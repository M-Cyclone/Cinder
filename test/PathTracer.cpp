#include <cstdint>
#include <fstream>
#include <memory>
#include <vector>

#include <eigen3/Eigen/Eigen>

#include <cinder/Cinder.h>

int main(int argc, char** argv)
{
    cinder::render::BasicDiffuseMaterial basic_red_diffuse(
        Eigen::Vector3f(0.63f, 0.065f, 0.05f));
    cinder::render::BasicDiffuseMaterial basic_green_diffuse(
        Eigen::Vector3f(0.14f, 0.45f, 0.091f));
    cinder::render::BasicDiffuseMaterial basic_white_diffuse(
        Eigen::Vector3f(0.725f, 0.71f, 0.68f));

    cinder::render::BasicEmitMaterial basic_emit_mat(
        Eigen::Vector3f(0.65f, 0.65f, 0.65f),
        Eigen::Vector3f(100.0f, 100.0f, 100.0f));


    auto scene = std::make_shared<cinder::core::Scene>();


    // Floor
    {
        std::vector<Eigen::Vector3f> vertices;
        vertices.emplace_back(552.8f, 0.0f, 0.0f);
        vertices.emplace_back(0.0f, 0.0f, 0.0f);
        vertices.emplace_back(0.0f, 0.0f, 559.2f);
        vertices.emplace_back(549.6f, 0.0f, 559.2f);
        vertices.emplace_back(556.0f, 548.8f, 0.0f);
        vertices.emplace_back(556.0f, 548.8f, 559.2f);
        vertices.emplace_back(0.0f, 548.8f, 559.2f);
        vertices.emplace_back(0.0f, 548.8f, 0.0f);
        vertices.emplace_back(549.6f, 0.0f, 559.2f);
        vertices.emplace_back(0.0f, 0.0f, 559.2f);
        vertices.emplace_back(0.0f, 548.8f, 559.2f);
        vertices.emplace_back(556.0f, 548.8, 559.2f);

        std::vector<size_t> indices{ 0, 1, 2, 2, 3, 0,  4,  5,  6,
                                     6, 7, 4, 8, 9, 10, 10, 11, 8 };

        for (size_t i = 0; i < indices.size(); i += 3)
        {
            scene->addTriangle(
                cinder::geometry::Triangle(vertices[indices[i]],
                                           vertices[indices[i + 1]],
                                           vertices[indices[i + 2]],
                                           &basic_white_diffuse));
        }
    }


    // Light
    {
        std::vector<Eigen::Vector3f> vertices;
        vertices.emplace_back(343.0f, 548.7f, 227.0f);
        vertices.emplace_back(343.0f, 548.7f, 332.0f);
        vertices.emplace_back(213.0f, 548.7f, 332.0f);
        vertices.emplace_back(213.0f, 548.7f, 227.0f);

        scene->addTriangle(cinder::geometry::Triangle(vertices[0],
                                                      vertices[1],
                                                      vertices[2],
                                                      &basic_emit_mat));
        scene->addTriangle(cinder::geometry::Triangle(vertices[0],
                                                      vertices[2],
                                                      vertices[3],
                                                      &basic_emit_mat));
    }


    Eigen::Vector3f camera_pos(278.0f, 273.0f, -800.0f);
    auto            camera = std::make_shared<cinder::geometry::Camera>(
        camera_pos,
        camera_pos + Eigen::Vector3f(0.0f, 0.0f, 1.0f));


    auto inte =
        std::make_shared<cinder::integrator::DirectLightingIntegrator>();


    cinder::render::Renderer renderer(640, 480);
    renderer.setCamera(camera);
    renderer.setScene(scene);
    renderer.setIntegrator(inte);
    renderer.setSPPCount(1);
    renderer.render();
    renderer.writeToPPM("output.ppm");
}