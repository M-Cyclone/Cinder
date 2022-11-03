#pragma once

#include <eigen3/Eigen/Eigen>

namespace cinder
{
namespace geometry
{

struct Vertex
{
    Vertex() noexcept = default;
    Vertex(Eigen::Vector3f p, Eigen::Vector3f n) noexcept : pos(p), normal(n) {}
    Vertex(const Vertex&)            = default;
    Vertex& operator=(const Vertex&) = default;

    static Vertex interpolate(const Vertex& v0,
                              const Vertex& v1,
                              const Vertex& v2,
                              float         u,
                              float         v)
    {
        float t = 1.0f - u - v;
        return Vertex{
            t * v0.pos + u * v1.pos + v * v2.pos,
            (t * v0.normal + u * v1.normal + v * v2.normal).normalized()
        };
    }

    Eigen::Vector3f pos;
    Eigen::Vector3f normal;
};

}  // namespace geometry
}  // namespace cinder