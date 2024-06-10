cmake_minimum_required(VERSION 3.24.2)

project(raytracer VERSION 0.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCES src/main.cpp
    src/Scene.cpp
    src/Sphere.cpp
    src/BlinnPhong.cpp
    src/GRY_Color.cpp
    )

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME}
    PRIVATE include
    )

configure_file(raytracerconfig.h.in raytracerconfig.h)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})