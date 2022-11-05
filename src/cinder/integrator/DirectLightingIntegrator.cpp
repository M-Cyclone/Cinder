#include "cinder/integrator/DirectLightingIntegrator.h"
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

Eigen::Vector3f DirectLightingIntegrator::integrate(const core::Scene&   scene,
                                                    const geometry::Ray& ray,
                                                    sampler::Sampler& spl) const
{
    geometry::Intersection hit_obj;
    if (!scene.cast(ray, hit_obj))
    {
        return Eigen::Vector3f(0.0f, 0.0f, 0.0f);
    }


    if (hit_obj.mat->hasEmission())
    {
        return hit_obj.mat->getEmission();
    }


    // Calculate direct lighting.
    Eigen::Vector3f L_dir(0.0f, 0.0f, 0.0f);
    {
        // Sample light.
        geometry::SamplePrimitiveResult hit_light = scene.sampleLight(spl);


        // Check if the light can be seen from hit_res.pos.
        Eigen::Vector3f light_dir = (hit_light.pos - hit_obj.pos);
        geometry::Ray   light_ray(hit_obj.pos, light_dir);

        geometry::Intersection collision_hit_res;
        scene.cast(light_ray, collision_hit_res);
        Eigen::Vector3f collision_vec = (collision_hit_res.pos - hit_obj.pos);

        // No blocked.
        if (light_dir.norm() < collision_hit_res.distance + utils::k_eps)
        {
            float cos_theta_light = hit_light.normal.dot(-light_ray.dir);

            // Can receive light.
            if (cos_theta_light > 0.0f)
            {
                float cos_theta_curr_obj = hit_obj.normal.dot(light_ray.dir);

                Eigen::Vector3f pos_diff          = hit_light.pos - hit_obj.pos;
                float           pos_diff_dist_sqr = pos_diff.dot(pos_diff);


                Eigen::Vector3f bsdf = hit_obj.mat->getBsdf(hit_obj.normal,
                                                            -ray.dir,
                                                            light_ray.dir);


                Eigen::Vector3f L_i = hit_light.mat->getEmission();

                L_dir = (L_i.array() * bsdf.array()).matrix() *
                        cos_theta_curr_obj * cos_theta_light /
                        (pos_diff_dist_sqr * hit_light.pdf);
            }
        }
    }

    return L_dir;
}

}  // namespace integrator
}  // namespace cinder