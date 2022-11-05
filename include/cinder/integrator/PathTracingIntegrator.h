#pragma once

#include "cinder/integrator/Integrator.h"

#include "cinder/geometry/Intersect.h"

namespace cinder
{
namespace integrator
{

class PathTracingIntegrator : public Integrator
{
public:
    PathTracingIntegrator() noexcept = default;

    virtual Eigen::Vector3f integrate(const core::Scene&   scene,
                                      const geometry::Ray& ray,
                                      sampler::Sampler&    spl) const override;

private:
    static Eigen::Vector3f shade(const core::Scene&      scene,
                                 const geometry::Ray&    ray,
                                 sampler::Sampler& const spl,
                                 geometry::Intersection& obj);
};

}  // namespace integrator
}  // namespace cinder