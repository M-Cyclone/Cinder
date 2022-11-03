#pragma once
#include <cmath>
#include <utility>

#include <eigen3/Eigen/Eigen>

#include "cinder/utils/MathHelper.h"

namespace cinder
{
namespace geometry
{

class Camera
{
public:
    Camera() noexcept = default;
    Camera(Eigen::Vector3f pos, Eigen::Vector3f focus) noexcept : m_pos(pos)
    {
        Eigen::Vector3f forward = (focus - pos).normalized();
        Eigen::Vector3f right =
            forward.cross(Eigen::Vector3f(0.0f, 1.0f, 0.0f)).normalized();
        Eigen::Vector3f up = right.cross(forward).normalized();

        Eigen::Matrix3f rotation_matrix;
        rotation_matrix << right.x(), up.x(), -forward.x(), right.y(), up.y(),
            -forward.y(), right.z(), up.z(), -forward.z();

        m_rotation = Eigen::Quaternionf(rotation_matrix);
    }

    Eigen::Vector3f getPosition() const { return m_pos; }
    Eigen::Matrix3f getRotation() const
    {
        return m_rotation.toRotationMatrix();
    }

    float getCameraHalfHeight() const
    {
        return std::tan(utils::angleToRadius(m_fov) * 0.5f);
    }

private:
    Eigen::Vector3f    m_pos;
    Eigen::Quaternionf m_rotation;

    float m_fov = 45.0f;
};

}  // namespace geometry
}  // namespace cinder