#pragma once
#include <algorithm>
#include <cmath>
#include <optional>

#include <Eigen/Eigen>

#include "cinder/utils/Constants.h"

namespace cinder
{
namespace geometry
{

struct Ray
{
    Ray() noexcept
        : pos(0.0f, 0.0f, 0.0f)
        , dir(0.0f, 1.0f, 0.0f)
        , dir_inv(utils::k_float_max, 1.0f, utils::k_float_max)
    {}
    Ray(Eigen::Vector3f pos, Eigen::Vector3f dir)
        : pos(pos)
        , dir(dir.normalized())
        , dir_inv(1.0f / this->dir.x(),
                  1.0f / this->dir.y(),
                  1.0f / this->dir.z())
    {}

    Eigen::Vector3f pos;
    Eigen::Vector3f dir;
    Eigen::Vector3f dir_inv;
};

}  // namespace geometry
}  // namespace cinder