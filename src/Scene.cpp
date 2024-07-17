#include "Scene.hpp"
#include "BlinnPhong.hpp"
#include "Ray.hpp"

void Scene::drawScene(const GRY_View& view, GRY_Ppm& ppm) {
    GRY_Color color;
    GRY_Color ambient{0.f, 0.f, 0.f, 1.f};
    for (auto& light : lights) { ambient += (light.color * light.intensity) * 0.025f; }
    for (int i = 0; i < view.rays.size(); i++) {
        if (castRay(view.origin, view.rays.at(i), color)) {
            ppm.frameBuffer.at(i) = color + ambient;
        }
    }
}

bool Scene::castRay(const Vec3f &origin, const Vec3f &nRay, GRY_Color& color, int reflect) {
    float leastDistanceToHit = -1.f;
    const Sphere* hitSphere = nullptr;
    const Plane* hitPlane = nullptr;

    for (const auto& sphere : spheres) {
        float distance;
        if (rayIntersectSphere(sphere, nRay, origin, &distance) && 
            ((distance < leastDistanceToHit || leastDistanceToHit < 0.f) && distance > 0.1f)) {
            leastDistanceToHit = distance;
            hitSphere = &sphere;
        }
    }
    for (const auto& plane : planes) {
        float distance;
        if (rayIntersectPlane(plane, nRay, origin, &distance) &&
            ((distance < leastDistanceToHit || leastDistanceToHit < 0.f) && distance > 0.1f)) {
                hitSphere = nullptr;
                leastDistanceToHit = distance;
                hitPlane = &plane;
            }
    }

    if (hitSphere || hitPlane) {
        Vec3f point = origin + (nRay * leastDistanceToHit);
        Vec3f N;
        GRY_Material mat;
        if (hitSphere) {
            N = GRY_VecNormalize(point - hitSphere->center);
            if (GRY_VecDot(nRay, N) > 0.f) { N *= -1.f; }
            mat = hitSphere->material;
        }
        else if (hitPlane) {
            N = GRY_VecDot(nRay, hitPlane->n) > 0.f ? hitPlane->n * -1.f : hitPlane->n;
            mat = hitPlane->material;
        }

        Vec3f rRay = nRay;
        if (reflect < reflectionLimit && (mat.reflect || mat.refract)) {
            if (mat.refract) {
                rRay = GRY_VecRefract(rRay, N, 1.f, mat.refractIndex);
            }
            if (mat.reflect) {
                rRay = GRY_VecReflect(rRay, N);
            }
            Vec3f eOrigin = GRY_VecDot(rRay, N) < 0.f ? point - (N * 1e-3f) : point + (N * 1e-3f);
            if (castRay(eOrigin, rRay, color, reflect+1)) { mat.diffuseColor = color; }
        }

        color = blinnPhong(this, mat, N, point, origin, nRay);
    }
    
    return hitSphere || hitPlane;
}

bool Scene::castRay(const Vec3f& origin, const Vec3f& nRay, const float* withinDistance) const {
    float distance;
    for (const auto& sphere : spheres) {
        if (rayIntersectSphere(sphere, nRay, origin, &distance) && !sphere.material.refract) {
            if (withinDistance && distance > *withinDistance) { continue; }
            return true;
        }
    }
    for (const auto& plane : planes) {
        if (rayIntersectPlane(plane, nRay, origin, &distance)) {
            if (withinDistance && distance > *withinDistance) { continue; }
            return true;
        }
    }

    return false;
}
