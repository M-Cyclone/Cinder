#include "cinder/render/BasicDiffuseMaterial.h"

namespace cinder
{
namespace render
{

Eigen::Vector3f BasicDiffuseMaterial::sampleRayDir(Eigen::Vector3f   normal,
                                                   Eigen::Vector3f   wi,
                                                   sampler::Sampler& spl) const
{
    float rand_1 = spl.getUniformFloat01();
    float rand_2 = spl.getUniformFloat01();

    float z   = std::abs(1.0f - 2.0f * rand_1);
    float r   = std::sqrt(1.0f - z * z);
    float phi = 2.0f * utils::k_pi * rand_2;

    Eigen::Vector3f local_ray_dir(r * std::cos(phi), r * std::sin(phi), z);

    return utils::vectorLocalToWorld(local_ray_dir, normal);
}

}  // namespace render
}  // namespace cinder