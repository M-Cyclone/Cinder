#include "cinder/integrator/DirectLightingIntegrator.h"
#include <cassert>
#include <cstdint>
#include <iostream>
#include <memory>

#include <eigen3/Eigen/Eigen>

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

Eigen::Vector3f DirectLightingIntegrator::integrate(
    const core::Scene&   scene,
    const geometry::Ray& ray) const
{
    geometry::Intersection hit_res;
    if (!scene.cast(ray, hit_res))
    {
        return Eigen::Vector3f(0.0f, 0.0f, 0.0f);
    }
    return Eigen::Vector3f(1.0f, 0.0f, 0.0f);

    if (hit_res.mat->hasEmission())
    {
        return hit_res.mat->getEmission();
    }
    assert(!hit_res.mat->hasEmission());


    // Calculate direct lighting.
    Eigen::Vector3f L_dir(0.0f, 0.0f, 0.0f);
    {
        // Sample light.
        geometry::SamplePrimitiveResult sample_res =
            scene.sampleLight(std::make_shared<sampler::Sampler>());


        // Check if the light can be seen from hit_res.pos.
        Eigen::Vector3f light_dir = (sample_res.pos - hit_res.pos);
        geometry::Ray   light_ray(hit_res.pos, light_dir);

        geometry::Intersection collision_hit_res;
        scene.cast(light_ray, collision_hit_res);
        Eigen::Vector3f collision_vec = (collision_hit_res.pos - hit_res.pos);

        // Check blocked.
        float light_distance_sqr     = light_dir.dot(light_dir);
        float collision_distance_sqr = collision_vec.dot(collision_vec);

        // No blocked.
        if (light_distance_sqr < utils::k_eps + collision_distance_sqr)
        {
            float cos_theta_light = sample_res.normal.dot(-light_ray.dir);

            // Can receive light.
            if (cos_theta_light > 0.0f)
            {
                float cos_theta_curr_obj = hit_res.normal.dot(light_ray.dir);

                Eigen::Vector3f pos_diff = sample_res.pos - hit_res.pos;
                float           pos_diff_dist_sqr = pos_diff.dot(pos_diff);


                Eigen::Vector3f bsdf = hit_res.mat->getBsdf(hit_res.normal,
                                                            -ray.dir,
                                                            light_ray.dir);


                Eigen::Vector3f L_i = sample_res.mat->getEmission();

                L_dir = (L_i.array() * bsdf.array()).matrix() *
                        cos_theta_curr_obj * cos_theta_light /
                        (pos_diff_dist_sqr * sample_res.pdf);
            }
        }
    }

    return L_dir;
}

}  // namespace integrator
}  // namespace cinder