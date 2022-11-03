cmake_minimum_required(VERSION 3.16)
project(Cinder)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Eigen3 3 REQUIRED)
find_package(TBB REQUIRED)

set(CINDER_HEADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include/cinder)
set(CINDER_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/cinder)

file(GLOB cinder_accelerate_files CONFIGURE_DEPENDS
    ${CINDER_HEADER_DIR}/accelerate/*.h
    ${CINDER_SOURCE_DIR}/accelerate/*.cpp
)
file(GLOB cinder_core_files CONFIGURE_DEPENDS
${CINDER_HEADER_DIR}/core/*.h
${CINDER_SOURCE_DIR}/core/*.cpp
)
file(GLOB cinder_geometry_files CONFIGURE_DEPENDS
${CINDER_HEADER_DIR}/geometry/*.h
${CINDER_SOURCE_DIR}/geometry/*.cpp
)
file(GLOB cinder_integrator_files CONFIGURE_DEPENDS
${CINDER_HEADER_DIR}/integrator/*.h
${CINDER_SOURCE_DIR}/integrator/*.cpp
)
file(GLOB cinder_render_files CONFIGURE_DEPENDS
    ${CINDER_HEADER_DIR}/render/*.h
    ${CINDER_SOURCE_DIR}/render/*.cpp
)
file(GLOB cinder_utils_files CONFIGURE_DEPENDS
    ${CINDER_HEADER_DIR}/utils/*.h
    ${CINDER_SOURCE_DIR}/utils/*.cpp
)

add_library(${PROJECT_NAME} SHARED
    ${cinder_accelerate_files}
    ${cinder_core_files}
    ${cinder_geometry_files}
    ${cinder_integrator_files}
    ${cinder_render_files}
    ${cinder_utils_files}
    ${CINDER_HEADER_DIR}/Cinder.h
)
target_include_directories(${PROJECT_NAME}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(${PROJECT_NAME}
    Eigen3::Eigen
    TBB::tbb
)

export(TARGETS ${PROJECT_NAME} NAMESPACE Cinder:: FILE CinderTargets.cmake)


add_executable(PathTracer
    ${CMAKE_CURRENT_SOURCE_DIR}/test/PathTracer.cpp
)
target_include_directories(PathTracer
    PRIVATE ${CINDER_HEADER_DIR}
)
target_link_libraries(PathTracer
    PRIVATE ${PROJECT_NAME}
)