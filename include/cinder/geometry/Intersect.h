#pragma once
#include <cstddef>
#include <tuple>

#include <eigen3/Eigen/Eigen>

#include "cinder/render/Material.h"

#include "cinder/geometry/Vertex.h"
#include "cinder/utils/Constants.h"

namespace cinder
{
namespace geometry
{

struct Intersection
{
    Intersection()
        : pos(0.0f, 0.0f, 0.0f)
        , normal(0.0f, 1.0f, 0.0f)
        , distance(utils::k_float_max)
        , mat(nullptr)
    {}
    Intersection(Eigen::Vector3f         p,
                 Eigen::Vector3f         n,
                 float                   dist,
                 const render::Material* m)
        : pos(p), normal(n), distance(dist), mat(m)
    {}
    Intersection(const Intersection&)            = default;
    Intersection& operator=(const Intersection&) = default;

    Eigen::Vector3f pos;
    Eigen::Vector3f normal;

    float distance;

    const render::Material* mat;
};

}  // namespace geometry
}  // namespace cinder