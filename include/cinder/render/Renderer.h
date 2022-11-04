#pragma once
#include <cstddef>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include <eigen3/Eigen/Eigen>

#include "cinder/core/Scene.h"

#include "cinder/geometry/Camera.h"
#include "cinder/geometry/Ray.h"

#include "cinder/integrator/Integrator.h"

namespace cinder
{
namespace render
{

struct RenderTask
{
    int32_t         pos_x;
    int32_t         pos_y;
    geometry::Ray   ray;
    Eigen::Vector3f res_color;
};

class Renderer
{
public:
    Renderer(int32_t width, int32_t height) noexcept;
    Renderer(const Renderer&)            = delete;
    Renderer& operator=(const Renderer&) = delete;

    void setScene(std::shared_ptr<core::Scene> scene) { m_scene = scene; }
    void setCamera(std::shared_ptr<geometry::Camera> camera)
    {
        m_camera = camera;
    }
    void setIntegrator(std::shared_ptr<integrator::Integrator> in)
    {
        m_integrator = in;
    }
    void setSPPCount(size_t count) { m_spp_count = count; }

    void render();

    void writeToPPM(const std::string& name);

private:
    void setColor(Eigen::Vector3f color, int32_t x, int32_t y)
    {
        m_panel[x + (m_height - y - 1) * m_width] = color;
    }

private:
    const int32_t                m_width;
    const int32_t                m_height;
    std::vector<Eigen::Vector3f> m_panel;

    size_t                                  m_spp_count = 1;
    std::shared_ptr<core::Scene>            m_scene;
    std::shared_ptr<geometry::Camera>       m_camera;
    std::shared_ptr<integrator::Integrator> m_integrator;
};

}  // namespace render
}  // namespace cinder