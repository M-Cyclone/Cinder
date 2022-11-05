#pragma once
#include <cstddef>

#include <Eigen/Eigen>

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
    Triangle(const Vertex&           v0,
             const Vertex&           v1,
             const Vertex&           v2,
             const render::Material* mat) noexcept
        : Primitive(mat)
        , v0{ v0 }
        , v1{ v1 }
        , v2{ v2 }
        , e1{ v1.pos - v0.pos }
        , e2{ v2.pos - v0.pos }
    {
        aabb.merge(v0.pos);
        aabb.merge(v1.pos);
        aabb.merge(v2.pos);
        center = (v0.pos + v1.pos + v2.pos) * (1.0f / 3.0f);

        surface_area     = 0.5f * e1.cross(e2).norm();
        surface_area_inv = 1.0f / surface_area;
    }
    Triangle(Eigen::Vector3f         p0,
             Eigen::Vector3f         p1,
             Eigen::Vector3f         p2,
             const render::Material* mat)
        : Primitive(mat), e1{ p1 - p0 }, e2{ p2 - p0 }
    {
        aabb.merge(p0);
        aabb.merge(p1);
        aabb.merge(p2);
        center = (p0 + p1 + p2) * (1.0f / 3.0f);

        Eigen::Vector3f normal = e1.cross(e2).normalized();
        v0                     = { p0, normal };
        v1                     = { p1, normal };
        v2                     = { p2, normal };

        surface_area     = 0.5f * e1.cross(e2).norm();
        surface_area_inv = 1.0f / surface_area;
    }
    Triangle(const Triangle&) noexcept            = default;
    Triangle& operator=(const Triangle&) noexcept = default;

    virtual bool                  cast(const Ray&              ray,
                                       geometry::Intersection& hit_res) const override;
    virtual SamplePrimitiveResult sample(sampler::Sampler& spl) const override;

    Vertex v0;
    Vertex v1;
    Vertex v2;

    Eigen::Vector3f e1;
    Eigen::Vector3f e2;
};

}  // namespace geometry
}  // namespace cinder