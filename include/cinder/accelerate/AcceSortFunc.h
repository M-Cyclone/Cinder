#pragma once
#include <vector>

#include "cinder/geometry/AABB.h"
#include "cinder/geometry/Primitive.h"

namespace cinder
{
namespace accelerate
{

enum class AcceSortAlgorithm
{
    BVH,
    SAH
};

template <typename T>
struct AcceSortFunc
{
    static geometry::AABB sortPrimitive(
        std::vector<const geometry::Primitive*>::iterator it_begin,
        std::vector<const geometry::Primitive*>::iterator it_end)
    {
        return T::sortPrimitive_Impl(it_begin, it_end);
    }
};

struct AcceSortFuncBVH : AcceSortFunc<AcceSortFuncBVH>
{
    friend struct AcceSortFunc<AcceSortFuncBVH>;

private:
    static geometry::AABB sortPrimitive_Impl(
        std::vector<const geometry::Primitive*>::iterator it_begin,
        std::vector<const geometry::Primitive*>::iterator it_end);
};

struct AcceSortFuncSAH : AcceSortFunc<AcceSortFuncSAH>
{
    friend struct AcceSortFunc<AcceSortFuncSAH>;

private:
    static geometry::AABB sortPrimitive_Impl(
        std::vector<const geometry::Primitive*>::iterator it_begin,
        std::vector<const geometry::Primitive*>::iterator it_end);
};

}  // namespace accelerate
}  // namespace cinder