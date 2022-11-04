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

    for (const geometry::Primitive* prim : m_primitives)
    {
        primitives.push_back(prim);
    }

    for (const geometry::Primitive* emit_tri : m_emit_primitives)
    {
        primitives.push_back(emit_tri);
    }

    m_acce_tree.recursiveBuild(std::move(primitives),
                               accelerate::AcceSortAlgorithm::BVH);
}

geometry::SamplePrimitiveResult Scene::sampleLight(
    std::shared_ptr<sampler::Sampler> spl) const
{
    float random_01        = spl->getUniformFloat01();
    float random_emit_area = random_01 * m_emit_surface_area_sum;


    float  curr_sum_area = 0.0f;
    size_t idx           = 0;
    for (const auto& emit_tri : m_emit_primitives)
    {
        if (curr_sum_area < random_emit_area)
        {
            ++idx;
            curr_sum_area += emit_tri->surface_area;
        }
        else
        {
            break;
        }
    }

    return m_emit_primitives[idx - 1]->sample(spl);
}

}  // namespace core
}  // namespace cinder