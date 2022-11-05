cmake_minimum_required(VERSION 3.16)
project(Cinder)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Eigen3 3 REQUIRED)

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
file(GLOB cinder_sampler_files CONFIGURE_DEPENDS
    ${CINDER_HEADER_DIR}/sampler/*.h
    ${CINDER_SOURCE_DIR}/sampler/*.cpp
)
file(GLOB cinder_utils_files CONFIGURE_DEPENDS
    ${CINDER_HEADER_DIR}/utils/*.h
    ${CINDER_SOURCE_DIR}/utils/*.cpp
)

if(MSVC)
    source_group(accelerate FILES ${cinder_accelerate_files})
    source_group(core       FILES ${cinder_core_files})
    source_group(geometry   FILES ${cinder_geometry_files})
    source_group(integrator FILES ${cinder_integrator_files})
    source_group(render     FILES ${cinder_render_files})
    source_group(sampler    FILES ${cinder_sampler_files})
    source_group(uitls      FILES ${cinder_utils_files})
endif()

add_library(${PROJECT_NAME} STATIC
    ${cinder_accelerate_files}
    ${cinder_core_files}
    ${cinder_geometry_files}
    ${cinder_integrator_files}
    ${cinder_render_files}
    ${cinder_sampler_files}
    ${cinder_utils_files}
    ${CINDER_HEADER_DIR}/Cinder.h
)
target_include_directories(${PROJECT_NAME}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
    PUBLIC ${EXTERNAL_DIR}/stb/include
)
target_link_libraries(${PROJECT_NAME}
    Eigen3::Eigen
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


if(MSVC)
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT PathTracer)
endif()