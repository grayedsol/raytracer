#pragma once
#include "LightSource.hpp"
#include "GRY_Material.hpp"
#include <vector>

struct Sphere {
    Vec3f center;
    float radius;
    GRY_Material material;
};

bool rayIntersect(const std::vector<Sphere>& spheres, const std::vector<Light>& lights, const Vec3f& origin, const Vec3f& ray, Vec3f& point, GRY_Color& color);
