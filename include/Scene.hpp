#pragma once
#include "Sphere.hpp"
#include "GRY_Ppm.hpp"

struct Scene {
    std::vector<Sphere> spheres;
    std::vector<LightSource> lights;

    void drawScene(const Vec3f& origin, const std::vector<Vec3f>& rays, GRY_Ppm& ppm);
};