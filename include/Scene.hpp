#pragma once
#include "Sphere.hpp"
#include "GRY_View.hpp"

struct Scene {
    static const int reflectionLimit = 4;
    std::vector<Sphere> spheres;
    std::vector<Light> lights;

    void drawScene(const GRY_View& view, GRY_Ppm& ppm);

    bool castRay(const Vec3f& origin, const Vec3f& nRay) const;

private:
    bool castRay(const Vec3f& origin, const Vec3f& nRay, GRY_Color& color);

    bool castRayReflect(const Vec3f& origin, const Vec3f& nRay, GRY_Color& color, int reflect = 0);
};