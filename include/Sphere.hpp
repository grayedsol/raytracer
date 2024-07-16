#pragma once
#include "Light.hpp"
#include "GRY_Material.hpp"
#include <vector>

struct Sphere {
    Vec3f center;
    float radius;
    GRY_Material material;
};

bool rayIntersectSphere(const Sphere& sphere, const Vec3f& nRay, const Vec3f& rayOrigin, float* distance = nullptr);