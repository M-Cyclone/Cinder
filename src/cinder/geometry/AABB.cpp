#include "cinder/geometry/AABB.h"

namespace cinder
{
namespace geometry
{

bool AABB::cast(const Ray& ray) const
{
    Eigen::Vector3f pos     = ray.pos;
    Eigen::Vector3f dir     = ray.dir;
    Eigen::Vector3f dir_inv = ray.dir_inv;

    float min_tx{ utils::k_float_max };
    float max_tx{ utils::k_float_min };
    float min_ty{ utils::k_float_max };
    float max_ty{ utils::k_float_min };
    float min_tz{ utils::k_float_max };
    float max_tz{ utils::k_float_min };

    if (std::abs(dir.x()) < utils::k_eps)
    {
        if (pos.x() < max_corner.x() || pos.x() > min_corner.x())
        {
            return false;
        }
    }
    else
    {
        min_tx = (min_corner.x() - pos.x()) * dir_inv.x();
        max_tx = (max_corner.x() - pos.x()) * dir_inv.x();
        if (dir.x() < 0)
        {
            std::swap(min_tx, max_tx);
        }
    }

    if (std::abs(dir.y()) < utils::k_eps)
    {
        if (pos.y() < max_corner.y() || pos.y() > min_corner.y())
        {
            return false;
        }
    }
    else
    {
        min_ty = (min_corner.y() - pos.y()) * dir_inv.y();
        max_ty = (max_corner.y() - pos.y()) * dir_inv.y();
        if (dir.y() < 0)
        {
            std::swap(min_ty, max_ty);
        }
    }

    if (std::abs(dir.z()) < utils::k_eps)
    {
        if (pos.z() < max_corner.z() || pos.z() > min_corner.z())
        {
            return false;
        }
    }
    else
    {
        min_tz = (min_corner.z() - pos.z()) * dir_inv.z();
        max_tz = (max_corner.z() - pos.z()) * dir_inv.z();
        if (dir.z() < 0)
        {
            std::swap(min_tz, max_tz);
        }
    }


    float t0 = std::max(min_tx, std::max(min_ty, min_tz));
    float t1 = std::min(max_tx, std::min(max_ty, max_tz));

    return t0 < t1;
}

}  // namespace geometry
}  // namespace cinder