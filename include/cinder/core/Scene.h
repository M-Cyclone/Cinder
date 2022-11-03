#pragma once
#include <utility>
#include <vector>

#include "cinder/accelerate/AcceTree.h"
#include "cinder/geometry/Intersect.h"
#include "cinder/geometry/Ray.h"
#include "cinder/geometry/Triangle.h"

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

    template <typename... Args>
    void addTriangle(Args&&... args)
    {
        m_triangles.emplace_back(std::forward<Args>(args)...);
    }

    bool cast(const geometry::Ray& ray, geometry::Intersection& hit_res) const;

private:
    accelerate::AcceTree m_acce_tree;

    std::vector<geometry::Triangle> m_triangles;
};

}  // namespace core
}  // namespace cinder