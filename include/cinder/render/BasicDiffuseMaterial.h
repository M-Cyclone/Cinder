#pragma once
#include <iostream>

#include <eigen3/Eigen/Eigen>

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

    virtual Eigen::Vector3f sampleRayDir(
        Eigen::Vector3f                   normal,
        Eigen::Vector3f                   wi,
        std::shared_ptr<sampler::Sampler> spl) const override
    {
        float rand_1 = spl->getUniformFloat01();
        float rand_2 = spl->getUniformFloat01();

        float z   = std::abs(1.0f - 2.0f * rand_1);
        float r   = std::sqrt(1.0f - z * z);
        float phi = 2.0f * utils::k_pi * rand_2;

        Eigen::Vector3f local_ray_dir(r * std::cos(phi), r * std::sin(phi), z);

        return utils::vectorLocalToWorld(local_ray_dir, normal);
    }

private:
    Eigen::Vector3f m_kd;
};

}  // namespace render
}  // namespace cinder