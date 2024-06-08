#include "Sphere.hpp"
#include "BlinnPhong.hpp"

bool rayIntersect(const std::vector<Sphere>& spheres, const std::vector<Light>& lights, const Vec3f& origin, const Vec3f& ray, Vec3f& point, GRY_Color& color) {
    float leastDistanceToHit = -1.0f;
    const Sphere* hitSphere = nullptr;
    for (auto& sphere : spheres) {
        float dc = GRY_VecDot(ray, sphere.center);
        if (dc <= 0) { continue; }

        float discriminant = (dc * dc) - GRY_VecDot(sphere.center, sphere.center) + (sphere.radius * sphere.radius);
        if (discriminant < 0) { continue; }

        float t = dc;
        if (discriminant > 0) { t -= sqrtf(discriminant); }

        if (t < leastDistanceToHit || leastDistanceToHit < 0) {
            leastDistanceToHit = t;
            hitSphere = &sphere;
        }
    }
    if (hitSphere) {
        point = origin + (ray * leastDistanceToHit);
        Vec3f N = GRY_VecNormalize(point - hitSphere->center);
        color = blinnPhong(lights, hitSphere->material, N, point, origin, ray);
        return true;
    }
    return false;
}