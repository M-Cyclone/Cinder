#include <cstdint>
#include <fstream>
#include <memory>

#include <cinder/Cinder.h>

#include <Eigen/src/Core/Matrix.h>
#include "integrator/Integrator.h"
#include "render/Renderer.h"

int main(int argc, char** argv)
{
    auto scene = std::make_shared<cinder::core::Scene>();

    cinder::geometry::Vertex v0(Eigen::Vector3f(0.0f, 1.0f, 0.0f),
                                Eigen::Vector3f(0.0f, 0.0f, 1.0f));
    cinder::geometry::Vertex v1(Eigen::Vector3f(-1.0f, -1.0f, 0.0f),
                                Eigen::Vector3f(0.0f, 0.0f, 1.0f));
    cinder::geometry::Vertex v2(Eigen::Vector3f(1.0f, -1.0f, 0.0f),
                                Eigen::Vector3f(0.0f, 0.0f, 1.0f));

    scene->addTriangle(cinder::geometry::Triangle(v0, v1, v2));


    auto camera = std::make_shared<cinder::geometry::Camera>(
        Eigen::Vector3f(0.0f, 0.0f, -3.0f),
        Eigen::Vector3f(0.0f, 0.0f, 0.0f));


    auto inte = std::make_shared<cinder::integrator::Integrator>();


    cinder::render::Renderer renderer(640, 480);
    renderer.setCamera(camera);
    renderer.setScene(scene);
    renderer.setIntegrator(inte);
    renderer.render();
    renderer.writeToFile("output.ppm");
}