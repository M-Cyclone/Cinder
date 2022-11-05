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

    float min_tx{ (min_corner.x() - pos.x()) * ray.dir_inv.x() };
    float min_ty{ (min_corner.y() - pos.y()) * ray.dir_inv.y() };
    float min_tz{ (min_corner.z() - pos.z()) * ray.dir_inv.z() };
    float max_tx{ (max_corner.x() - pos.x()) * ray.dir_inv.x() };
    float max_ty{ (max_corner.y() - pos.y()) * ray.dir_inv.y() };
    float max_tz{ (max_corner.z() - pos.z()) * ray.dir_inv.z() };

    if (ray.dir.x() < 0) std::swap(min_tx, max_tx);
    if (ray.dir.y() < 0) std::swap(min_ty, max_ty);
    if (ray.dir.z() < 0) std::swap(min_tz, max_tz);

    float t_enter = std::max(min_tx, std::max(min_ty, min_tz));
    float t_exit  = std::min(max_tx, std::min(max_ty, max_tz));

    return t_enter <= t_exit && t_exit >= 0;
}

}  // namespace geometry
}  // namespace cinder