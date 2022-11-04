#pragma once
#include <iostream>

#include <eigen3/Eigen/Eigen>

#include "cinder/render/BasicDiffuseMaterial.h"

namespace cinder
{
namespace render
{

class BasicEmitMaterial : public BasicDiffuseMaterial
{
public:
    explicit BasicEmitMaterial(Eigen::Vector3f kd,
                               Eigen::Vector3f emit_intensity)
        : BasicDiffuseMaterial(kd), m_emit_intensity{ emit_intensity }
    {}
    virtual ~BasicEmitMaterial() noexcept = default;

    virtual bool            hasEmission() const override { return true; }
    virtual Eigen::Vector3f getEmission() const override
    {
        return m_emit_intensity;
    }

private:
    Eigen::Vector3f m_emit_intensity;
};

}  // namespace render
}  // namespace cinder