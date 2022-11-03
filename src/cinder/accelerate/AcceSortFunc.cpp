#include "cinder/accelerate/AcceSortFunc.h"
#include "cinder/geometry/AABB.h"

namespace cinder
{
namespace accelerate
{

geometry::AABB AcceSortFuncBVH::sortPrimitive_Impl(
    std::vector<const geometry::Primitive*>::iterator it_begin,
    std::vector<const geometry::Primitive*>::iterator it_end)
{
    geometry::AABB aabb;
    for (auto it = it_begin; it != it_end; ++it)
    {
        aabb.merge((*it)->aabb);
    }

    switch (aabb.getMaxExtentDir())
    {
    case geometry::AABB::MaxExtentDir::X:
    {
        std::sort(it_begin,
                  it_end,
                  [](const geometry::Primitive* prim1,
                     const geometry::Primitive* prim2)
                  {
                      return prim1->center.x() < prim2->center.x();
                  });
        break;
    }
    case geometry::AABB::MaxExtentDir::Y:
    {
        std::sort(it_begin,
                  it_end,
                  [](const geometry::Primitive* prim1,
                     const geometry::Primitive* prim2)
                  {
                      return prim1->center.y() < prim2->center.y();
                  });
        break;
    }
    case geometry::AABB::MaxExtentDir::Z:
    {
        std::sort(it_begin,
                  it_end,
                  [](const geometry::Primitive* prim1,
                     const geometry::Primitive* prim2)
                  {
                      return prim1->center.z() < prim2->center.z();
                  });
        break;
    }
    default:
        assert(false && "Not supported.");
    }

    return aabb;
}

geometry::AABB AcceSortFuncSAH::sortPrimitive_Impl(
    std::vector<const geometry::Primitive*>::iterator it_begin,
    std::vector<const geometry::Primitive*>::iterator it_end)
{
    return {};
}

}  // namespace accelerate
}  // namespace cinder