#pragma once
#include "gryvec.hpp"
#include <vector>

struct Sphere {
    Vec3f center;
    float radius;
    Vec3f color;
};

bool rayIntersect(Vec3f& origin, std::vector<Sphere>& spheres, std::vector<Vec3f>& rays) {
    return true;
}

bool rayIntersect(const Sphere& sphere, const Vec3f& origin, const Vec3f& ray) {
    Vec3f toSphere = sphere.center - origin;
    float dotProd = GRY_VecDot(toSphere, ray);

    if (dotProd <= 0) {
        return false;
    }

    Vec3f pd = ray * dotProd;
    return GRY_VecDistanceSq(sphere.center, pd) < (sphere.radius * sphere.radius);
}

bool rayIntersect(const std::vector<Sphere>& spheres, const Vec3f& origin, const Vec3f& ray, Vec3f& color) {
    float leastDistance = -1.0f;
    for (auto& sphere : spheres) {
        Vec3f toSphere = sphere.center - origin;
        float dotProd = GRY_VecDot(toSphere, ray);
        if (dotProd <= 0) { continue; }

        Vec3f pd = ray * dotProd;
        float distance = GRY_VecDistanceSq(sphere.center, pd);
        if (distance >= (sphere.radius*sphere.radius)) { continue; }

        if (distance < leastDistance || leastDistance == -1.0f) {
            leastDistance = distance;
            color = sphere.color;
        }
    }

    return leastDistance != -1.0f;
}
