#pragma once
#include <memory>

#include <eigen3/Eigen/Eigen>

#include "cinder/render/Material.h"

#include "cinder/geometry/AABB.h"
#include "cinder/geometry/Intersect.h"
#include "cinder/geometry/Ray.h"

#include "cinder/sampler/Sampler.h"

namespace cinder
{
namespace geometry
{

struct SamplePrimitiveResult
{
    Eigen::Vector3f         pos;
    Eigen::Vector3f         normal;
    float                   pdf;
    const render::Material* mat;
};

struct Primitive
{
    explicit Primitive(const render::Material* mat) noexcept
        : surface_area(0.0f), surface_area_inv(0.0f), material(mat)
    {}

    // Return the hit point's distance to the ray origin.
    virtual bool cast(const Ray&              ray,
                      geometry::Intersection& hit_res) const = 0;

    virtual SamplePrimitiveResult sample(
        std::shared_ptr<sampler::Sampler> spl) const = 0;

    float                   surface_area;
    float                   surface_area_inv;
    AABB                    aabb;
    Eigen::Vector3f         center;
    const render::Material* material;
};

}  // namespace geometry
}  // namespace cinder