#pragma once
#include "gryvec.hpp"
#include <vector>

struct Sphere {
    Vec3f center;
    float radius;
    Vec3f color;
};

// bool rayIntersect(Vec3f& origin, std::vector<Sphere>& spheres, std::vector<Vec3f>& rays) {
//     return true;
// }

// bool rayIntersect(const Sphere& sphere, const Vec3f& origin, const Vec3f& ray) {
//     Vec3f toSphere = sphere.center - origin;
//     float dotProd = GRY_VecDot(toSphere, ray);

//     if (dotProd <= 0) {
//         return false;
//     }

//     Vec3f pc = ray * dotProd;
//     return GRY_VecDistanceSq(sphere.center, pc) < (sphere.radius * sphere.radius);
// }

// bool rayIntersect(const std::vector<Sphere>& spheres, const Vec3f& origin, const Vec3f& ray, Vec3f& color) {
//     float leastDistance = -1.0f;
//     for (auto& sphere : spheres) {
//         Vec3f toSphere = sphere.center - origin;
//         float dotProd = GRY_VecDot(toSphere, ray);
//         if (dotProd <= 0) { continue; }

//         Vec3f pc = ray * dotProd;
//         float distance = GRY_VecDistanceSq(sphere.center, pc);
//         if (distance >= (sphere.radius*sphere.radius)) { continue; }

//         if (distance < leastDistance || leastDistance == -1.0f) {
//             leastDistance = distance;
//             color = sphere.color;
//         }
//     }

//     return leastDistance != -1.0f;
// }

bool rayIntersect(const std::vector<Sphere>& spheres, const Vec3f& origin, const Vec3f& ray, Vec3f& point, Vec3f& color) {
    float leastDistanceToHit = -1.0f;
    for (auto& sphere : spheres) {
        Vec3f toSphere = sphere.center - origin;
        float dotProd = GRY_VecDot(toSphere, ray);
        if (dotProd <= 0) { continue; }

        Vec3f pc = ray * dotProd;
        float inDistance = GRY_VecDistanceSq(sphere.center, pc);
        float hypotenuse = sphere.radius * sphere.radius;
        if (inDistance >= hypotenuse) { continue; }
        float side1 = GRY_VecDistanceSq(sphere.center, pc);
        float side3 = sqrtf(hypotenuse - side1);
        float distanceToHit = sqrtf(GRY_VecDistanceSq(origin, pc)) - side3;
        

        if (distanceToHit < leastDistanceToHit || leastDistanceToHit == -1.0f) {
            leastDistanceToHit = distanceToHit;
            color = sphere.color;
            point = origin + (ray * distanceToHit);
        }
    }
    return leastDistanceToHit != -1.0f;
}
