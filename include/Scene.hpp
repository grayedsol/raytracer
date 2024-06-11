#pragma once
#include "Sphere.hpp"
#include "GRY_View.hpp"

struct Scene {
    std::vector<Sphere> spheres;
    std::vector<Light> lights;

    void drawScene(const GRY_View& view, GRY_Ppm& ppm);

    bool castRay(const Vec3f& origin, const Vec3f& nRay) const;

private:
    bool castRay(const Vec3f& origin, const Vec3f& nRay, GRY_Color& color);
};