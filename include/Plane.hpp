#pragma once
#include "Light.hpp"
#include "GRY_Material.hpp"
#include <vector>

struct Plane {
    Vec3f n;
    float d;
    GRY_Material material;
};

bool rayIntersectPlane(const Plane& plane, const Vec3f& nRay, const Vec3f& rayOrigin, float* distance = nullptr);