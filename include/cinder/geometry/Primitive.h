#pragma once

#include <eigen3/Eigen/Eigen>

#include "cinder/render/Material.h"

#include "cinder/geometry/AABB.h"
#include "cinder/geometry/Intersect.h"
#include "cinder/geometry/Ray.h"

namespace cinder
{
namespace geometry
{

struct Primitive
{
    explicit Primitive(const render::Material* mat = nullptr) noexcept
        : material(mat)
    {}

    // Return the hit point's distance to the ray origin.
    virtual bool cast(const Ray& ray, Intersection& hit_res) const = 0;

    AABB                    aabb;
    Eigen::Vector3f         center;
    const render::Material* material;
};

}  // namespace geometry
}  // namespace cinder