#include "cinder/integrator/PathTracingIntegrator.h"
#include <cassert>
#include <cstdint>
#include <iostream>
#include <memory>

#include <Eigen/Eigen>

#include "cinder/geometry/Intersect.h"
#include "cinder/geometry/Primitive.h"
#include "cinder/geometry/Ray.h"
#include "cinder/sampler/Sampler.h"
#include "cinder/utils/Constants.h"
#include "cinder/utils/MathHelper.h"

namespace cinder
{
namespace integrator
{

Eigen::Vector3f PathTracingIntegrator::integrate(const core::Scene&   scene,
                                                 const geometry::Ray& ray,
                                                 sampler::Sampler&    spl) const
{
    geometry::Intersection hit_obj;
    if (!scene.cast(ray, hit_obj))
    {
        return Eigen::Vector3f(0.0f, 0.0f, 0.0f);
    }

    return shade(scene, ray, spl, hit_obj);
    
}

Eigen::Vector3f PathTracingIntegrator::shade(const core::Scene&      scene,
                                             const geometry::Ray&    ray,
                                             sampler::Sampler& const spl,
                                             geometry::Intersection& obj)
{
    if (obj.mat->hasEmission() && ray.dir.dot(obj.normal) < 0.0f)
    {
        return obj.mat->getEmission();
    }


    // Calculate direct lighting.
    Eigen::Vector3f Lo_dir(0.0f, 0.0f, 0.0f);
    {
        // Sample light.
        geometry::SamplePrimitiveResult hit_light = scene.sampleLight(spl);


        // Check if the light can be seen from hit_res.pos.
        Eigen::Vector3f light_dir = (hit_light.pos - obj.pos);
        geometry::Ray   light_ray(obj.pos, light_dir);

        geometry::Intersection collision_hit_res;
        scene.cast(light_ray, collision_hit_res);
        Eigen::Vector3f collision_vec = (collision_hit_res.pos - obj.pos);

        // No blocked.
        if (light_dir.norm() < collision_hit_res.distance + utils::k_eps)
        {
            float cos_theta_light = hit_light.normal.dot(-light_ray.dir);

            // Can receive light.
            if (cos_theta_light > 0.0f)
            {
                float cos_theta_curr_obj = obj.normal.dot(light_ray.dir);

                Eigen::Vector3f pos_diff          = hit_light.pos - obj.pos;
                float           pos_diff_dist_sqr = pos_diff.dot(pos_diff);


                Eigen::Vector3f bsdf =
                    obj.mat->getBsdf(obj.normal, -ray.dir, light_ray.dir);


                Eigen::Vector3f L_i = hit_light.mat->getEmission();

                Lo_dir = (L_i.array() * bsdf.array()).matrix() *
                         cos_theta_curr_obj * cos_theta_light /
                         (pos_diff_dist_sqr * hit_light.pdf);
            }
        }
    }


    // Calculate indirect lighting.
    Eigen::Vector3f Lo_indir(0.0f, 0.0f, 0.0f);
    {
        if (spl.getUniformFloat01() < utils::k_russian_roulette)
        {
            Eigen::Vector3f wi = -ray.dir;
            Eigen::Vector3f wo =
                obj.mat->sampleRayDir(obj.normal, wi, spl).normalized();
            float pdf = obj.mat->sampleDirPdf(obj.normal, wi, wo);

            if (pdf > utils::k_eps)
            {
                geometry::Ray          next_ray(obj.pos, wo);
                geometry::Intersection hit_next;

                if (scene.cast(next_ray, hit_next) &&
                    !hit_next.mat->hasEmission())
                {
                    float cos_theta      = std::max(0.0f, wo.dot(obj.normal));
                    Eigen::Vector3f bsdf = obj.mat->getBsdf(obj.normal, wi, wo);

                    Eigen::Vector3f irradiance =
                        shade(scene, next_ray, spl, hit_next);

                    Lo_indir = (irradiance.array() * bsdf.array()).matrix() *
                               cos_theta / (pdf * utils::k_russian_roulette);
                }
            }
        }
    }


    return Lo_dir + Lo_indir;
}

}  // namespace integrator
}  // namespace cinder