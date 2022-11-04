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
    Eigen::Vector3f e1 = v1.pos - v0.pos;
    Eigen::Vector3f e2 = v2.pos - v0.pos;


    Eigen::Vector3f p_vec = ray.dir.cross(e2);

    float det = p_vec.dot(e1);
    if (det < utils::k_eps) return false;
    float det_inv = 1.0f / det;


    Eigen::Vector3f t_vec = ray.pos - v0.pos;

    float u = t_vec.dot(p_vec) * det_inv;
    if (u < 0.0f || u > 1.0f) return false;


    Eigen::Vector3f q_vec = t_vec.cross(e1);

    float v = ray.dir.dot(q_vec) * det_inv;
    if (v < 0.0f || u + v > 1.0f) return false;


    float t = e2.dot(q_vec) * det_inv;
    if (t < utils::k_eps) return false;


    hit_res = Intersection(
        ray.pos + t * ray.dir,
        ((1.0f - u - v) * v0.normal + u * v1.normal + v * v2.normal)
            .normalized(),
        t,
        material);

    return true;
}

SamplePrimitiveResult Triangle::sample(
    std::shared_ptr<sampler::Sampler> spl) const
{
    float rand_u      = spl->getUniformFloat01();
    float rand_v      = spl->getUniformFloat01();
    float rand_sqrt_v = std::sqrt(rand_v);

    float a = (1.0f - rand_u) * rand_sqrt_v;
    float b = rand_u * rand_sqrt_v;
    float c = (1.0f - rand_sqrt_v);


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