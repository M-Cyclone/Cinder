#pragma once
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <functional>
#include <iostream>
#include <memory>
#include <vector>
#include <type_traits>

#include "cinder/accelerate/AcceSortFunc.h"

#include "cinder/geometry/AABB.h"
#include "cinder/geometry/Intersect.h"
#include "cinder/geometry/Primitive.h"
#include "cinder/geometry/Ray.h"
#include "cinder/geometry/Triangle.h"
#include "cinder/geometry/Vertex.h"

#include "cinder/utils/Constants.h"

namespace cinder
{
namespace accelerate
{

struct AcceNode
{
    AcceNode() noexcept = default;
    AcceNode(const geometry::AABB&      aabb,
             std::unique_ptr<AcceNode>  left,
             std::unique_ptr<AcceNode>  right,
             const geometry::Primitive* prim)
        : aabb(aabb)
        , left(std::move(left))
        , right(std::move(right))
        , primitive(prim)
    {}

    bool cast(const geometry::Ray& ray, geometry::Intersection& hit_res) const;

    geometry::AABB            aabb;
    std::unique_ptr<AcceNode> left;
    std::unique_ptr<AcceNode> right;

    const geometry::Primitive* primitive;
};

class AcceTree
{
public:
    AcceTree() noexcept = default;

    void recursiveBuild(std::vector<const geometry::Primitive*> prims,
                        AcceSortAlgorithm                       sort_algo);

    bool cast(const geometry::Ray& ray, geometry::Intersection& hit_res) const
    {
        return m_root && m_root->cast(ray, hit_res);
    }

private:
    template <typename SortFuncType>
        requires std::is_base_of_v<AcceSortFunc<SortFuncType>, SortFuncType>
    static std::unique_ptr<AcceNode> recursiveBuild(
        std::vector<const geometry::Primitive*>::iterator it_begin,
        std::vector<const geometry::Primitive*>::iterator it_end)
    {
        if (it_begin == it_end) return nullptr;


        size_t prim_count = it_end - it_begin;
        if (prim_count == 1)
        {
            return std::make_unique<AcceNode>((*it_begin)->aabb,
                                              nullptr,
                                              nullptr,
                                              (*it_begin));
        }


        geometry::AABB aabb = SortFuncType::sortPrimitive(it_begin, it_end);

        size_t half_count = (prim_count >> 1);

        std::unique_ptr<AcceNode> left =
            recursiveBuild<SortFuncType>(it_begin, it_begin + half_count);
        std::unique_ptr<AcceNode> right =
            recursiveBuild<SortFuncType>(it_begin + half_count, it_end);


        return std::make_unique<AcceNode>(aabb,
                                          std::move(left),
                                          std::move(right),
                                          nullptr);
    }

private:
    std::unique_ptr<AcceNode> m_root;
};

}  // namespace accelerate
}  // namespace cinder