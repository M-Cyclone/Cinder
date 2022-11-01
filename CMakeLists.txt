cmake_minimum_required(VERSION 3.16)
project(Cinder)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON1)

find_package(glm REQUIRED)

set(CINDER_HEADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include/cinder)
set(CINDER_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/cinder)

file(GLOB cinder_core_files CONFIGURE_DEPENDS
    ${CINDER_HEADER_DIR}/core/*.h
    ${CINDER_SOURCE_DIR}/core/*.cpp
)
file(GLOB cinder_geometry_files CONFIGURE_DEPENDS
    ${CINDER_HEADER_DIR}/geometry/*.h
    ${CINDER_SOURCE_DIR}/geometry/*.cpp
)

add_library(${PROJECT_NAME} SHARED
    ${cinder_core_files}
    ${cinder_geometry_files}
    ${CINDER_HEADER_DIR}/Cinder.h
)
target_include_directories(${PROJECT_NAME}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(${PROJECT_NAME}
    glm::glm
)

export(TARGETS ${PROJECT_NAME} NAMESPACE Cinder:: FILE CinderTargets.cmake)


add_executable(PathTracer
    ${CMAKE_CURRENT_SOURCE_DIR}/test/PathTracer.cpp
)
target_link_libraries(PathTracer
    PRIVATE 
)