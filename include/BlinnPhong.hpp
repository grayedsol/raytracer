#pragma once
#include "Sphere.hpp"

GRY_Color phongReflect(const std::vector<Light>& lights, const GRY_Material& material, const Vec3f& N, const Vec3f& point, const Vec3f& origin, const Vec3f& ray);