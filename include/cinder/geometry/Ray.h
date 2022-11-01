#pragma once

#include <glm/geometric.hpp>
#include <glm/glm.hpp>

namespace cinder
{
namespace geometry
{

struct Ray
{
    Ray() noexcept : pos(0.0f, 0.0f, 0.0f), dir(0.0f, 1.0f, 0.0f) {}
    Ray(glm::vec3 pos, glm::vec3 dir) : pos(pos), dir(glm::normalize(dir)) {}

    glm::vec3 pos;
    glm::vec3 dir;
};

}  // namespace geometry
}  // namespace cinder