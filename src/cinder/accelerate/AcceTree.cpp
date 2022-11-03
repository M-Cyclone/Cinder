#include "cinder/accelerate/AcceTree.h"
#include <algorithm>
#include <cassert>
#include <iostream>
#include <memory>
#include <vector>

#include "cinder/accelerate/AcceSortFunc.h"

namespace cinder
{
namespace accelerate
{

bool AcceNode::cast(const geometry::Ray&    ray,
                    geometry::Intersection& hit_res) const
{
    if (!left && !right)
    {
        return primitive->cast(ray, hit_res);
    }


    geometry::Intersection left_hit_res;
    bool                   hit_left =
        (left && left->aabb.cast(ray) && left->cast(ray, left_hit_res));

    geometry::Intersection right_hit_res;
    bool                   hit_right =
        (right && right->aabb.cast(ray) && right->cast(ray, right_hit_res));


    if (!hit_left && !hit_right) return false;

    hit_res = (left_hit_res.distance < right_hit_res.distance) ? left_hit_res
                                                               : right_hit_res;
    return true;
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