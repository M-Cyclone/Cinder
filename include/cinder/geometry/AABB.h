#pragma once
#include <cassert>
#include <cmath>
#include <vector>

#include <eigen3/Eigen/Eigen>

#include "cinder/geometry/Ray.h"

#include "cinder/utils/Constants.h"

namespace cinder
{
namespace geometry
{

struct AABB
{
    enum class MaxExtentDir
    {
        None,
        X,
        Y,
        Z
    };

    AABB()
    noexcept
        : min_corner(utils::k_float_max, utils::k_float_max, utils::k_float_max)
        , max_corner(utils::k_float_min, utils::k_float_min, utils::k_float_min)
    {}
    AABB(const std::vector<Eigen::Vector3f>& points)
    noexcept
        : min_corner(utils::k_float_max, utils::k_float_max, utils::k_float_max)
        , max_corner(utils::k_float_min, utils::k_float_min, utils::k_float_min)
    {
        for (auto p : points)
        {
            merge(p);
        }
    }

    AABB& merge(Eigen::Vector3f p)
    {
        min_corner.x() = std::min(min_corner.x(), p.x());
        min_corner.y() = std::min(min_corner.y(), p.y());
        min_corner.z() = std::min(min_corner.z(), p.z());
        max_corner.x() = std::max(max_corner.x(), p.x());
        max_corner.y() = std::max(max_corner.y(), p.y());
        max_corner.z() = std::max(max_corner.z(), p.z());

        return *this;
    }

    AABB& merge(const AABB& rhs)
    {
        min_corner.x() = std::min(min_corner.x(), rhs.min_corner.x());
        min_corner.y() = std::min(min_corner.y(), rhs.min_corner.y());
        min_corner.z() = std::min(min_corner.z(), rhs.min_corner.z());
        max_corner.x() = std::max(max_corner.x(), rhs.max_corner.x());
        max_corner.y() = std::max(max_corner.y(), rhs.max_corner.y());
        max_corner.z() = std::max(max_corner.z(), rhs.max_corner.z());

        return *this;
    }

    MaxExtentDir getMaxExtentDir() const
    {
        float x = max_corner.x() - min_corner.x();
        float y = max_corner.y() - min_corner.y();
        float z = max_corner.z() - min_corner.z();

        if (x >= y && x >= z) return MaxExtentDir::X;
        if (y >= x && y >= z) return MaxExtentDir::Y;
        if (z >= x && z >= y) return MaxExtentDir::Z;

        assert(false && "Should not be here.");
        return MaxExtentDir::None;
    }

    bool cast(const Ray& ray) const;

    Eigen::Vector3f min_corner;
    Eigen::Vector3f max_corner;
};

}  // namespace geometry
}  // namespace cinder