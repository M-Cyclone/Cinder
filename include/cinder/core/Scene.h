#pragma once
#include <memory>
#include <optional>
#include <utility>
#include <vector>

#include <Eigen/Eigen>

#include "cinder/accelerate/AcceTree.h"
#include "cinder/geometry/Intersect.h"
#include "cinder/geometry/Primitive.h"
#include "cinder/geometry/Ray.h"
#include "cinder/geometry/Triangle.h"
#include "cinder/sampler/Sampler.h"

namespace cinder
{
namespace core
{

class Scene
{
public:
    Scene() noexcept               = default;
    Scene(const Scene&)            = delete;
    Scene& operator=(const Scene&) = delete;
    ~Scene() noexcept              = default;

    void createAcceTree();

    void addTriangle(const geometry::Triangle tri)
    {
        if (tri.material->hasEmission())
        {
            m_emit_surface_area_sum += tri.surface_area;
            m_emit_triangles.push_back(tri);
        }
        else
        {
            m_triangles.push_back(tri);
        }
    }

    bool cast(const geometry::Ray& ray, geometry::Intersection& hit_res) const
    {
        return m_acce_tree.cast(ray, hit_res);
    }

    geometry::SamplePrimitiveResult sampleLight(sampler::Sampler& spl) const;

private:
    accelerate::AcceTree m_acce_tree;

    std::vector<geometry::Triangle> m_triangles;
    std::vector<geometry::Triangle> m_emit_triangles;
    float                           m_emit_surface_area_sum;
};

}  // namespace core
}  // namespace cinder