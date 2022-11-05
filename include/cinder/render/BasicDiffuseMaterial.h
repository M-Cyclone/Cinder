#pragma once
#include <iostream>

#include <Eigen/Eigen>

#include "cinder/render/Material.h"

#include "cinder/utils/Constants.h"
#include "cinder/utils/MathHelper.h"

namespace cinder
{
namespace render
{

class BasicDiffuseMaterial : public Material
{
public:
    explicit BasicDiffuseMaterial(Eigen::Vector3f kd) : m_kd{ kd } {}
    virtual ~BasicDiffuseMaterial() noexcept = default;

    virtual bool            hasEmission() const override { return false; }
    virtual Eigen::Vector3f getEmission() const override
    {
        return Eigen::Vector3f(0.0f, 0.0f, 0.0f);
    }

    virtual Eigen::Vector3f getBsdf(Eigen::Vector3f normal,
                                    Eigen::Vector3f wi,
                                    Eigen::Vector3f wo) const override
    {
        float cos_theta = wo.dot(normal);
        return (cos_theta > 0.0f) ? (m_kd * utils::k_pi_inv)
                                  : Eigen::Vector3f(0.0f, 0.0f, 0.0f);
    }

    virtual Eigen::Vector3f sampleRayDir(Eigen::Vector3f   normal,
                                         Eigen::Vector3f   wi,
                                         sampler::Sampler& spl) const override;
    virtual float           sampleDirPdf(Eigen::Vector3f normal,
                                         Eigen::Vector3f wi,
                                         Eigen::Vector3f wo) const override
    {
        return (normal.dot(wi) < 0.0f) ? 0.0f : (0.5f * utils::k_pi_inv);
    }

private:
    Eigen::Vector3f m_kd;
};

}  // namespace render
}  // namespace cinder