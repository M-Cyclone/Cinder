#include "cinder/geometry/Triangle.h"
#include <iostream>

#include "cinder/geometry/Intersect.h"

#include "cinder/utils/Constants.h"

namespace cinder
{
namespace geometry
{

bool Triangle::cast(const Ray& ray, Intersection& hit_res) const
{
    // Möller-Trumbore algorithm
    Eigen::Vector3f e1 = v1.pos - v0.pos;
    Eigen::Vector3f e2 = v2.pos - v0.pos;


    Eigen::Vector3f p_vec = ray.dir.cross(e2);

    float det = p_vec.dot(e1);
    if (std::abs(det) < utils::k_eps) return false;
    float det_inv = 1.0f / det;


    Eigen::Vector3f t_vec = ray.pos - v0.pos;

    float u = t_vec.dot(p_vec) * det_inv;
    if (u < 0.0f || u > 1.0f) return false;


    Eigen::Vector3f q_vec = t_vec.cross(e1);

    float v = ray.dir.dot(q_vec) * det_inv;
    if (v < 0.0f || u + v > 1.0f) return false;


    float t = e2.dot(q_vec) * det_inv;
    if (t < utils::k_eps) return false;


    hit_res.pos = ray.pos + t * ray.dir;
    hit_res.normal =
        ((1.0f - u - v) * v0.normal + u * v1.normal + v * v2.normal)
            .normalized();
    hit_res.distance = t;
    hit_res.mat      = material;

    return true;
}

}  // namespace geometry
}  // namespace cinder