#include "cinder/render/Renderer.h"
#include <cassert>
#include <fstream>
#include <vector>

#include <oneapi/tbb/blocked_range.h>
#include <oneapi/tbb/parallel_for.h>

namespace cinder
{
namespace render
{

Renderer::Renderer(int32_t width, int32_t height) noexcept
    : m_width(width)
    , m_height(height)
    , m_panel(width * height, Eigen::Vector3f(0.0f, 0.0f, 0.0f))
{}

void Renderer::render()
{
    assert(m_camera);
    assert(m_scene);
    assert(m_integrator);

    m_scene->createAcceTree();


    Eigen::Vector3f camera_pos      = m_camera->getPosition();
    Eigen::Matrix3f camera_rotation = m_camera->getRotation();
    Eigen::Vector3f camera_right    = Eigen::Vector3f(camera_rotation(0, 0),
                                                   camera_rotation(1, 0),
                                                   camera_rotation(2, 0));
    Eigen::Vector3f camera_up       = Eigen::Vector3f(camera_rotation(0, 1),
                                                camera_rotation(1, 1),
                                                camera_rotation(2, 1));
    Eigen::Vector3f camera_forward  = Eigen::Vector3f(-camera_rotation(0, 2),
                                                     -camera_rotation(1, 2),
                                                     -camera_rotation(2, 2));


    float camera_half_height = m_camera->getCameraHalfHeight();
    float camera_half_width =
        camera_half_height * (float)m_width / (float)m_height;

    float width_inv  = 1.0f / m_width;
    float height_inv = 1.0f / m_height;

    std::vector<RenderTask> render_tasks;
    for (int32_t y = 0; y < m_height; ++y)
    {
        for (int32_t x = 0; x < m_width; ++x)
        {
            float u = ((float)x + 0.5f) * width_inv * 2.0f - 1.0f;
            float v = ((float)y + 0.5f) * height_inv * 2.0f - 1.0f;

            Eigen::Vector3f dir =
                (camera_forward + u * camera_right * camera_half_width +
                 v * camera_up * camera_half_height)
                    .normalized();

            geometry::Ray ray(camera_pos, dir);

            render_tasks.push_back({ x, y, ray });
        }
    }


    float spp_count_inv = 1.0f / m_spp_count;
    for (auto& rt : render_tasks)
    {
        rt.res_color = Eigen::Vector3f(0.0f, 0.0f, 0.0f);
        for (size_t k = 0; k < m_spp_count; ++k)
        {
            rt.res_color += m_integrator->integrate(*m_scene, rt.ray);
        }
        rt.res_color *= spp_count_inv;
    }


    // tbb::parallel_for(
    //     tbb::blocked_range<size_t>(0, render_tasks.size()),
    //     [&](tbb::blocked_range<size_t> r)
    //     {
    //         for (size_t i = r.begin(); i < r.end(); ++i)
    //         {
    //             render_tasks[i].res_color = Eigen::Vector3f(0.0f, 0.0f,
    //             0.0f); for (size_t k = 0; k < m_spp_count; ++k)
    //             {
    //                 render_tasks[i].res_color +=
    //                     m_integrator->integrate(*m_scene,
    //                     render_tasks[i].ray);
    //             }
    //         }
    //     });

    for (const auto& rt : render_tasks)
    {
        setColor(rt.res_color, rt.pos_x, rt.pos_y);
    }
}

void Renderer::writeToPPM(const std::string& name)
{
    std::ofstream file(name);
    file << "P3 " << m_width << ' ' << m_height << ' ' << 255 << ' ';

    for (Eigen::Vector3f color : m_panel)
    {
        uint32_t r =
            (uint32_t)(255 * std::pow(std::clamp(color.x(), 0.0f, 1.0f), 0.6f));
        uint32_t g =
            (uint32_t)(255 * std::pow(std::clamp(color.y(), 0.0f, 1.0f), 0.6f));
        uint32_t b =
            (uint32_t)(255 * std::pow(std::clamp(color.z(), 0.0f, 1.0f), 0.6f));

        file << r << ' ' << g << ' ' << b << ' ';
    }
}

}  // namespace render
}  // namespace cinder