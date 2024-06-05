#include "sphere.hpp"

bool rayIntersect(const std::vector<Sphere>& spheres, const std::vector<LightSource>& lights, const Vec3f& origin, const Vec3f& ray, Vec3f& point, GRY_Color& color) {
    float leastDistanceToHit = -1.0f;
    for (auto& sphere : spheres) {
        Vec3f toSphere = sphere.center - origin;
        float dotProd = GRY_VecDot(toSphere, ray);
        if (dotProd <= 0) { continue; }

        Vec3f pc = ray * dotProd;
        float inDistance = GRY_VecDistanceSq(sphere.center, pc);
        float hypotenuse = sphere.radius * sphere.radius;
        if (inDistance >= hypotenuse) { continue; }
        float side1 = GRY_VecDistanceSq(sphere.center, pc);
        float side3 = sqrtf(hypotenuse - side1);
        float distanceToHit = sqrtf(GRY_VecDistanceSq(origin, pc)) - side3;
        

        if (distanceToHit < leastDistanceToHit || leastDistanceToHit == -1.0f) {
            leastDistanceToHit = distanceToHit;
            point = origin + (ray * distanceToHit);
            Vec3f hitDirFromSphere = GRY_VecNormalize(point - sphere.center);

            float intensity = 0.0f;
            for (auto& light : lights) {
                Vec3f lightDir = GRY_VecNormalize(light.position - point);
                float dotProd = GRY_VecDot(lightDir, hitDirFromSphere);
                if (dotProd <= 0) { continue; }
                intensity += light.intensity * dotProd;
            }

            color = (sphere.color * intensity);
        }
    }
    return leastDistanceToHit != -1.0f;
}