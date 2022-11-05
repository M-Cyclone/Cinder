#include "cinder/accelerate/AcceTree.h"
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iostream>
#include <memory>
#include <optional>
#include <vector>

#include "cinder/accelerate/AcceSortFunc.h"

namespace cinder
{
namespace accelerate
{

bool AcceNode::cast(const geometry::Ray&    ray,
                    geometry::Intersection& hit_res) const
{
    if (primitive)
    {
        return primitive->cast(ray, hit_res);
    }
    assert((left || right));


    geometry::Intersection l_hit_res;
    bool                   l_is_hit =
        (left && left->aabb.cast(ray) && left->cast(ray, l_hit_res));

    geometry::Intersection r_hit_res;
    bool                   r_is_hit =
        (right && right->aabb.cast(ray) && right->cast(ray, r_hit_res));


    if (!l_is_hit && !r_is_hit) return false;


    hit_res = (l_hit_res.distance < r_hit_res.distance) ? l_hit_res : r_hit_res;
    return hit_res.distance != utils::k_float_max;
}

void AcceTree::recursiveBuild(std::vector<const geometry::Primitive*> prims,
                              AcceSortAlgorithm                       sort_algo)
{
    switch (sort_algo)
    {
    case AcceSortAlgorithm::BVH:
    {
        std::cout << "Start to Build Tree with BVH." << std::endl;
        m_root = recursiveBuild<AcceSortFuncBVH>(prims.begin(), prims.end());
        std::cout << "Finish to Build Tree with BVH." << std::endl;
        assert(m_root && "Root node should not be nullptr.");
        break;
    }
    case AcceSortAlgorithm::SAH:
    {
        m_root = recursiveBuild<AcceSortFuncSAH>(prims.begin(), prims.end());
        break;
    }
    default:
        assert(false && "Not available sort algorithm.");
    }

    assert(!prims.empty());
}

}  // namespace accelerate
}  // namespace cinder