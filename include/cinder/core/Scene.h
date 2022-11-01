#pragma once

#include "cinder/geometry/Ray.h"

namespace cinder
{
namespace core
{

class Scene
{
public:
    Scene()                        = default;
    Scene(const Scene&)            = delete;
    Scene& operator=(const Scene&) = delete;
    ~Scene() noexcept              = default;
};

}  // namespace core
}  // namespace cinder