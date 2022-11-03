#pragma once
#include <cstdint>
#include <vector>

#include <eigen3/Eigen/Eigen>

#include "cinder/core/Scene.h"

#include "cinder/geometry/Ray.h"

namespace cinder
{
namespace integrator
{

class Integrator
{
public:
    Integrator() noexcept                             = default;
    Integrator(const Integrator&) noexcept            = default;
    Integrator& operator=(const Integrator&) noexcept = default;
    virtual ~Integrator() noexcept                    = default;

    virtual Eigen::Vector3f integrate(const core::Scene&   scene,
                                      const geometry::Ray& ray) const;
};

}  // namespace integrator
}  // namespace cinder