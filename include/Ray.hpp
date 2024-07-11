#pragma once
#include "GRY_Vec.hpp"

inline Vec3f GRY_VecReflect(const Vec3f& nRay, const Vec3f& N) {
    return nRay + (N * GRY_VecDot(nRay, N) * -2.0f);
}

inline Vec3f GRY_VecRefract(const Vec3f& nRay, const Vec3f& N, const float refract1, const float refract2) {
    float q = refract1 / refract2;
    float dot = GRY_VecDot(nRay, N) * -1.0f;
    float root = 1 - (q * q) + ((q * q) * (dot * dot));
    return (nRay * q) + (N * ((q * dot) - sqrtf(root)));
}