#pragma once

#include "cinder/integrator/Integrator.h"

namespace cinder
{
namespace integrator
{

class DirectLightingIntegrator : public Integrator
{
public:
    DirectLightingIntegrator() noexcept = default;

    virtual Eigen::Vector3f integrate(const core::Scene&   scene,
                                      const geometry::Ray& ray) const;
};

}  // namespace integrator
}  // namespace cinder