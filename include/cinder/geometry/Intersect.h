#pragma once
#include <tuple>

#include <eigen3/Eigen/Eigen>

#include "cinder/render/Material.h"

#include "cinder/geometry/Vertex.h"

namespace cinder
{
namespace geometry
{

struct Intersection
{
    Eigen::Vector3f pos;
    Eigen::Vector3f normal;

    float distance;

    const render::Material* mat = nullptr;
};

}  // namespace geometry
}  // namespace cinder