#include <cstdint>
#include <fstream>
#include <memory>
#include <vector>

#include <Eigen/Eigen>

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
        8.0f * Eigen::Vector3f(0.747f + 0.058f, 0.747f + 0.258f, 0.747f) +
            15.6f * Eigen::Vector3f(0.740f + 0.287f, 0.740f + 0.160f, 0.740f) +
            18.4f * Eigen::Vector3f(0.737f + 0.642f, 0.737f + 0.159f, 0.737f));


    auto scene = std::make_shared<cinder::core::Scene>();


    std::vector<cinder::geometry::Triangle> triangles;


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
        vertices.emplace_back(556.0f, 548.8f, 559.2f);

        std::vector<size_t> indices{ 1, 2, 3, 3, 4,  1,  5,  6,  7,
                                     7, 8, 5, 9, 10, 11, 11, 12, 9 };

        for (size_t i = 0; i < indices.size(); i += 3)
        {
            cinder::geometry::Triangle tri(vertices[indices[i] - 1],
                                           vertices[indices[i + 1] - 1],
                                           vertices[indices[i + 2] - 1],
                                           &basic_white_diffuse);
            scene->addTriangle(tri);
        }
    }


    // Left
    {
        std::vector<Eigen::Vector3f> vertices;
        vertices.emplace_back(552.8f, 0.0f, 0.0f);
        vertices.emplace_back(549.6f, 0.0f, 559.2f);
        vertices.emplace_back(556.0f, 548.8f, 559.2f);
        vertices.emplace_back(556.0f, 548.8f, 0.0f);

        cinder::geometry::Triangle tri1(vertices[0],
                                        vertices[1],
                                        vertices[2],
                                        &basic_red_diffuse);
        scene->addTriangle(tri1);

        cinder::geometry::Triangle tri2(vertices[0],
                                        vertices[2],
                                        vertices[3],
                                        &basic_red_diffuse);
        scene->addTriangle(tri2);
    }


    // Right
    {
        std::vector<Eigen::Vector3f> vertices;
        vertices.emplace_back(0.0f, 0.0f, 559.2f);
        vertices.emplace_back(0.0f, 0.0f, 0.0f);
        vertices.emplace_back(0.0f, 548.8f, 0.0f);
        vertices.emplace_back(0.0f, 548.8f, 559.2f);

        cinder::geometry::Triangle tri1(vertices[0],
                                        vertices[1],
                                        vertices[2],
                                        &basic_green_diffuse);
        scene->addTriangle(tri1);

        cinder::geometry::Triangle tri2(vertices[0],
                                        vertices[2],
                                        vertices[3],
                                        &basic_green_diffuse);
        scene->addTriangle(tri2);
    }


    // Tall box
    {
        std::vector<Eigen::Vector3f> vertices;
        vertices.emplace_back(423.0f, 330.0f, 247.0f);
        vertices.emplace_back(265.0f, 330.0f, 296.0f);
        vertices.emplace_back(314.0f, 330.0f, 456.0f);
        vertices.emplace_back(472.0f, 330.0f, 406.0f);
        vertices.emplace_back(423.0f, 0.0f, 247.0f);
        vertices.emplace_back(423.0f, 330.0f, 247.0f);
        vertices.emplace_back(472.0f, 330.0f, 406.0f);
        vertices.emplace_back(472.0f, 0.0f, 406.0f);
        vertices.emplace_back(472.0f, 0.0f, 406.0f);
        vertices.emplace_back(472.0f, 330.0f, 406.0f);
        vertices.emplace_back(314.0f, 330.0f, 456.0f);
        vertices.emplace_back(314.0f, 0.0f, 456.0f);
        vertices.emplace_back(314.0f, 0.0f, 456.0f);
        vertices.emplace_back(314.0f, 330.0f, 456.0f);
        vertices.emplace_back(265.0f, 330.0f, 296.0f);
        vertices.emplace_back(265.0f, 0.0f, 296.0f);
        vertices.emplace_back(265.0f, 0.0f, 296.0f);
        vertices.emplace_back(265.0f, 330.0f, 296.0f);
        vertices.emplace_back(423.0f, 330.0f, 247.0f);
        vertices.emplace_back(423.0f, 0.0f, 247.0f);

        std::vector<size_t> indices{ 1,  2,  3,  1,  3,  4,  5,  6,  7,  5,
                                     7,  8,  9,  10, 11, 9,  11, 12, 13, 14,
                                     15, 13, 15, 16, 17, 18, 19, 17, 19, 20 };

        for (size_t i = 0; i < indices.size(); i += 3)
        {
            cinder::geometry::Triangle tri(vertices[indices[i] - 1],
                                           vertices[indices[i + 1] - 1],
                                           vertices[indices[i + 2] - 1],
                                           &basic_white_diffuse);
            scene->addTriangle(tri);
        }
    }


    // Short box
    {
        std::vector<Eigen::Vector3f> vertices;
        vertices.emplace_back(130.0f, 165.0f, 65.0f);
        vertices.emplace_back(82.0f, 165.0f, 225.0f);
        vertices.emplace_back(240.0f, 165.0f, 272.0f);
        vertices.emplace_back(290.0f, 165.0f, 114.0f);
        vertices.emplace_back(290.0f, 0.0f, 114.0f);
        vertices.emplace_back(290.0f, 165.0f, 114.0f);
        vertices.emplace_back(240.0f, 165.0f, 272.0f);
        vertices.emplace_back(240.0f, 0.0f, 272.0f);
        vertices.emplace_back(130.0f, 0.0f, 65.0f);
        vertices.emplace_back(130.0f, 165.0f, 65.0f);
        vertices.emplace_back(290.0f, 165.0f, 114.0f);
        vertices.emplace_back(290.0f, 0.0f, 114.0f);
        vertices.emplace_back(82.0f, 0.0f, 225.0f);
        vertices.emplace_back(82.0f, 165.0f, 225.0f);
        vertices.emplace_back(130.0f, 165.0f, 65.0f);
        vertices.emplace_back(130.0f, 0.0f, 65.0f);
        vertices.emplace_back(240.0f, 0.0f, 272.0f);
        vertices.emplace_back(240.0f, 165.0f, 272.0f);
        vertices.emplace_back(82.0f, 165.0f, 225.0f);
        vertices.emplace_back(82.0f, 0.0f, 225.0f);

        std::vector<size_t> indices{ 1,  2,  3,  1,  3,  4,  5,  6,  7,  5,
                                     7,  8,  9,  10, 11, 9,  11, 12, 13, 14,
                                     15, 13, 15, 16, 17, 18, 19, 17, 19, 20 };

        for (size_t i = 0; i < indices.size(); i += 3)
        {
            cinder::geometry::Triangle tri(vertices[indices[i] - 1],
                                           vertices[indices[i + 1] - 1],
                                           vertices[indices[i + 2] - 1],
                                           &basic_white_diffuse);
            scene->addTriangle(tri);
        }
    }


    // Light
    {
        std::vector<Eigen::Vector3f> vertices;
        vertices.emplace_back(343.0f, 548.7f, 227.0f);
        vertices.emplace_back(343.0f, 548.7f, 332.0f);
        vertices.emplace_back(213.0f, 548.7f, 332.0f);
        vertices.emplace_back(213.0f, 548.7f, 227.0f);

        cinder::geometry::Triangle tri1(vertices[0],
                                        vertices[1],
                                        vertices[2],
                                        &basic_emit_mat);
        scene->addTriangle(tri1);

        cinder::geometry::Triangle tri2(vertices[0],
                                        vertices[2],
                                        vertices[3],
                                        &basic_emit_mat);
        scene->addTriangle(tri2);
    }


    Eigen::Vector3f camera_pos(278.0f, 273.0f, -800.0f);
    auto            camera = std::make_shared<cinder::geometry::Camera>(
        camera_pos,
        camera_pos + Eigen::Vector3f(0.0f, 0.0f, 1.0f));


    auto inte =
        std::make_shared<cinder::integrator::PathTracingIntegrator>();


    cinder::core::Renderer renderer(1024, 1024);
    renderer.setCamera(camera);
    renderer.setScene(scene);
    renderer.setIntegrator(inte);
    renderer.setSPPCount(128);
    renderer.setSampler(std::make_unique<cinder::sampler::Sampler>());
    renderer.render();
    renderer.writeToPNG("output.png");
}