#pragma once
#include "Sphere.hpp"

GRY_Color phongReflect(const std::vector<Light>& lights, const Sphere& sphere, const Vec3f& hit, const Vec3f& origin, const Vec3f& ray);