#include "cinder/core/Scene.h"

#include "cinder/accelerate/AcceSortFunc.h"
#include "cinder/geometry/Primitive.h"

namespace cinder
{
namespace core
{

void Scene::createAcceTree()
{
    std::vector<const geometry::Primitive*> primitives;

    for (const auto& tri : m_triangles)
    {
        primitives.push_back(&tri);
    }

    m_acce_tree.recursiveBuild(std::move(primitives),
                               accelerate::AcceSortAlgorithm::BVH);
}

bool Scene::cast(const geometry::Ray&    ray,
                 geometry::Intersection& hit_res) const
{
    return m_acce_tree.cast(ray, hit_res);
}

}  // namespace core
}  // namespace cinder