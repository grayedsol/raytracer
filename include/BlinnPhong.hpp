#pragma once
#include "Sphere.hpp"

GRY_Color phong(const std::vector<Light>& lights, const GRY_Material& material, const Vec3f& N, const Vec3f& point, const Vec3f& origin, const Vec3f& ray);

GRY_Color blinnPhong(const std::vector<Light>& lights, const GRY_Material& material, const Vec3f& N, const Vec3f& point, const Vec3f& origin, const Vec3f& ray);