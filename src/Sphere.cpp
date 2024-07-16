#include "Sphere.hpp"

bool rayIntersectSphere(const Sphere &sphere, const Vec3f &nRay, const Vec3f &rayOrigin, float *distance) {
    Vec3f offsetCenter = sphere.center - rayOrigin;
    float dc = GRY_VecDot(nRay, offsetCenter);
    if (dc <= 0 && (GRY_VecDistanceSq(rayOrigin, sphere.center) > sphere.radius * sphere.radius)) { return false; }

    float discriminant = (dc * dc) - GRY_VecDot(offsetCenter, offsetCenter) + (sphere.radius * sphere.radius);
    if (discriminant < 0) { return false; }

    if (distance) {
        float sqrtDiscriminant = sqrtf(discriminant);
        if (sphere.material.refract && dc < sqrtDiscriminant) { return false; }
        *distance = dc > sqrtDiscriminant ? dc - sqrtDiscriminant : dc + sqrtDiscriminant;
    }
    return true;
}
