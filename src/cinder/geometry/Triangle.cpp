#include "cinder/geometry/Triangle.h"
#include <cmath>
#include <iostream>

#include "cinder/geometry/Intersect.h"

#include "cinder/geometry/Primitive.h"
#include "cinder/utils/Constants.h"

namespace cinder
{
namespace geometry
{

bool Triangle::cast(const Ray& ray, geometry::Intersection& hit_res) const
{
    // Möller-Trumbore algorithm

    Eigen::Vector3f p_vec = ray.dir.cross(e2);

    float det = p_vec.dot(e1);
    if (det < utils::k_eps) return false;
    float det_inv = 1.0f / det;


    Eigen::Vector3f t_vec = ray.pos - v0.pos;

    float u = t_vec.dot(p_vec) * det_inv;
    if (u < 0.0f || u > 1.0f) return false;


    Eigen::Vector3f q_vec = t_vec.cross(e1);

    float v = ray.dir.dot(q_vec) * det_inv;
    if ((v < 0.0f) || (u + v > 1.0f)) return false;


    float t = e2.dot(q_vec) * det_inv;
    if (t <= 0.0f) return false;


    hit_res.pos = ray.pos + t * ray.dir;
    hit_res.normal =
        ((1.0f - u - v) * v0.normal + u * v1.normal + v * v2.normal)
            .normalized();
    hit_res.distance = t;
    hit_res.mat      = material;

    return true;
}

SamplePrimitiveResult Triangle::sample(sampler::Sampler& spl) const
{
    float rand_u = std::sqrt(spl.getUniformFloat01());
    float rand_v = spl.getUniformFloat01();

    float a = 1.0f - rand_u;
    float b = rand_u * (1.0f - rand_v);
    float c = rand_u * rand_v;


    SamplePrimitiveResult sample_res;
    sample_res.pos = a * v0.pos + b * v1.pos + c * v2.pos;
    sample_res.normal =
        (a * v0.normal + b * v1.normal + c * v2.normal).normalized();
    sample_res.pdf = surface_area_inv;
    sample_res.mat = material;

    return sample_res;
}

}  // namespace geometry
}  // namespace cinder