#pragma once
#include "Sphere.hpp"

class Scene;

GRY_Color phong(const Scene* scene, const GRY_Material& material, const Vec3f& N, const Vec3f& point, const Vec3f& origin, const Vec3f& ray);

GRY_Color blinnPhong(const Scene* scene, const GRY_Material& material, const Vec3f& N, const Vec3f& point, const Vec3f& origin, const Vec3f& ray);