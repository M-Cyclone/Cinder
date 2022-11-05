#include "cinder/core/Scene.h"
#include <cassert>

#include "cinder/accelerate/AcceSortFunc.h"
#include "cinder/geometry/Primitive.h"
#include "cinder/render/Material.h"

namespace cinder
{
namespace core
{

void Scene::createAcceTree()
{
    std::vector<const geometry::Primitive*> primitives;

    for (const geometry::Triangle& tri : m_triangles)
    {
        primitives.push_back(&tri);
    }

    for (const geometry::Triangle& emit_tri : m_emit_triangles)
    {
        primitives.push_back(&emit_tri);
    }

    m_acce_tree.recursiveBuild(std::move(primitives),
                               accelerate::AcceSortAlgorithm::BVH);
}

geometry::SamplePrimitiveResult Scene::sampleLight(sampler::Sampler& spl) const
{
    float random_01        = spl.getUniformFloat01();
    float random_emit_area = random_01 * m_emit_surface_area_sum;


    float curr_sum_area = 0.0f;
    for (const auto& emit_tri : m_emit_triangles)
    {
        curr_sum_area += emit_tri.surface_area;
        if (curr_sum_area >= random_emit_area)
        {
            return emit_tri.sample(spl);
        }
    }

    assert(false && "Should not be here.");
    return {};
}

}  // namespace core
}  // namespace cinder