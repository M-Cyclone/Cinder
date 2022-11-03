#pragma once
#include <cstddef>

#include <eigen3/Eigen/Eigen>

#include "cinder/render/Material.h"

#include "cinder/geometry/Intersect.h"
#include "cinder/geometry/Primitive.h"
#include "cinder/geometry/Vertex.h"

namespace cinder
{
namespace geometry
{

struct Triangle : Primitive
{
    explicit Triangle(const render::Material* mat = nullptr) noexcept
        : Primitive(mat), v0{}, v1{}, v2{}
    {}
    Triangle(const Vertex&           v0,
             const Vertex&           v1,
             const Vertex&           v2,
             const render::Material* mat = nullptr) noexcept
        : Primitive(mat), v0{ v0 }, v1{ v1 }, v2{ v2 }
    {
        aabb.merge(v0.pos);
        aabb.merge(v1.pos);
        aabb.merge(v2.pos);
        center = (v0.pos + v1.pos + v2.pos) * (1.0f / 3.0f);
    }
    Triangle(const Triangle&) noexcept            = default;
    Triangle& operator=(const Triangle&) noexcept = default;

    virtual bool cast(const Ray& ray, Intersection& hit_res) const override;

    Vertex v0;
    Vertex v1;
    Vertex v2;
};

}  // namespace geometry
}  // namespace cinder