#include "cinder/integrator/Integrator.h"
#include <cstdint>
#include <iostream>

#include "cinder/geometry/Intersect.h"

namespace cinder
{
namespace integrator
{

Eigen::Vector3f Integrator::integrate(const core::Scene&   scene,
                                      const geometry::Ray& ray) const
{
    geometry::Intersection hit_res;
    if (scene.cast(ray, hit_res))
    {
        return { 1.0f, 1.0f, 1.0f };
    }

    return { 0.0f, 0.0f, 0.0f };
}

}  // namespace integrator
}  // namespace cinder