#include "Sphere.hpp"

bool rayIntersectSphere(const Sphere& sphere, const Vec3f& nRay, float* distance) {
    float dc = GRY_VecDot(nRay, sphere.center);
    if (dc <= 0) { return false; }

    float discriminant = (dc * dc) - GRY_VecDot(sphere.center, sphere.center) + (sphere.radius * sphere.radius);
    if (discriminant < 0) { return false; }

    if (distance) {
        *distance = (discriminant > 0) ? (dc - sqrt(discriminant)) : (dc);
    }
    return true;
}

bool rayIntersectSphere(const Sphere &sphere, const Vec3f &nRay, const Vec3f &rayOrigin, float *distance) {
    Vec3f offsetCenter = sphere.center - rayOrigin;
    float dc = GRY_VecDot(nRay, offsetCenter);
    if (dc <= 0) { return false; }

    float discriminant = (dc * dc) - GRY_VecDot(offsetCenter, offsetCenter) + (sphere.radius * sphere.radius);
    if (discriminant < 0) { return false; }

    if (distance) {
        *distance = (discriminant > 0) ? (dc - sqrt(discriminant)) : (dc);
    }
    return true;
}
