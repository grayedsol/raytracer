#pragma once
#include "Sphere.hpp"
#include "Plane.hpp"
#include "GRY_View.hpp"

struct Scene {
    static const int reflectionLimit = 4;
    std::vector<Sphere> spheres;
    std::vector<Plane> planes;
    std::vector<Light> lights;

    void drawScene(const GRY_View& view, GRY_Ppm& ppm);

    bool castRay(const Vec3f& origin, const Vec3f& nRay, const float* withinDistance = nullptr) const;

private:
    bool castRay(const Vec3f& origin, const Vec3f& nRay, GRY_Color& color, int reflect = 0);
};