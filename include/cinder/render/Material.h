#pragma once
#include <iostream>
#include <memory>

#include <Eigen/Eigen>

#include "cinder/sampler/Sampler.h"

namespace cinder
{
namespace render
{

class Material
{
public:
    Material() noexcept          = default;
    virtual ~Material() noexcept = default;

    virtual bool            hasEmission() const = 0;
    virtual Eigen::Vector3f getEmission() const = 0;

    virtual Eigen::Vector3f getBsdf(Eigen::Vector3f normal,
                                    Eigen::Vector3f wi,
                                    Eigen::Vector3f wo) const = 0;

    virtual Eigen::Vector3f sampleRayDir(Eigen::Vector3f   normal,
                                         Eigen::Vector3f   wi,
                                         sampler::Sampler& spl) const = 0;
    virtual float           sampleDirPdf(Eigen::Vector3f normal,
                                         Eigen::Vector3f wi,
                                         Eigen::Vector3f wo) const    = 0;
};

}  // namespace render
}  // namespace cinder