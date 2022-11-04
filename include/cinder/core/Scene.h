#pragma once
#include <memory>
#include <optional>
#include <utility>
#include <vector>

#include <eigen3/Eigen/Eigen>

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

    void addTriangle(const geometry::Primitive& prim)
    {
        if (prim.material->hasEmission())
        {
            m_emit_surface_area_sum += prim.surface_area;
            m_emit_primitives.push_back(&prim);
        }
        else
        {
            m_primitives.push_back(&prim);
        }
    }

    bool cast(const geometry::Ray& ray, geometry::Intersection& hit_res) const
    {
        return m_acce_tree.cast(ray, hit_res);
    }

    geometry::SamplePrimitiveResult sampleLight(
        std::shared_ptr<sampler::Sampler> spl) const;

private:
    accelerate::AcceTree m_acce_tree;

    std::vector<const geometry::Primitive*> m_primitives;
    std::vector<const geometry::Primitive*> m_emit_primitives;
    float                                   m_emit_surface_area_sum;
};

}  // namespace core
}  // namespace cinder