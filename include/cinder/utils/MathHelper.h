#pragma once

#include <Eigen/Eigen>

#include "cinder/utils/Constants.h"

namespace cinder
{
namespace utils
{

static float angleToRadius(float angle)
{
    return angle * k_pi * (1.0f / 180.0f);
}

static Eigen::Vector3f vectorWorldToLocal(Eigen::Vector3f vec,
                                          Eigen::Vector3f nor)
{
    return vec;
}

static Eigen::Vector3f vectorLocalToWorld(Eigen::Vector3f vec,
                                          Eigen::Vector3f nor)
{
    Eigen::Vector3f C;

    if (std::abs(nor.x()) > std::abs(nor.y()))
    {
        float inv_len = 1.0f / std::sqrt(nor.x() * nor.x() + nor.z() * nor.z());
        C = Eigen::Vector3f(nor.z() * inv_len, 0.0f, -nor.x() * inv_len);
    }
    else
    {
        float inv_len = 1.0f / std::sqrt(nor.y() * nor.y() + nor.z() * nor.z());
        C = Eigen::Vector3f(0.0f, nor.z() * inv_len, -nor.y() * inv_len);
    }


    Eigen::Vector3f B = C.cross(nor);

    return vec.x() * B + vec.y() * C + vec.z() * nor;
}

}  // namespace utils
}  // namespace cinder