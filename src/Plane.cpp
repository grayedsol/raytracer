#include "Plane.hpp"

bool rayIntersectPlane(const Plane &plane, const Vec3f &nRay, const Vec3f &rayOrigin, float *distance) {
    float d = GRY_VecDot(plane.n, nRay);
    if (d == 0.0f) { return false; }
    float t = -((GRY_VecDot(plane.n, rayOrigin) - plane.d) / d);
    if (t <= 0.0f) { return false; }
    if (distance) { *distance = t; }
    return true;
}
