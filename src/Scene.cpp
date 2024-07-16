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

    for (auto& sphere : spheres) {
        float distance;
        if (rayIntersectSphere(sphere, nRay, origin, &distance) && 
            ((distance < leastDistanceToHit || leastDistanceToHit < 0.f) && distance > 0.1f)) {
            hitPlane = nullptr;
            leastDistanceToHit = distance;
            hitSphere = &sphere;
        }
    }
    for (auto& plane : planes) {
        float distance;
        if (rayIntersectPlane(plane, nRay, origin, &distance) &&
            ((distance < leastDistanceToHit || leastDistanceToHit < 0.f) && distance > 0.1f)) {
                hitSphere = nullptr;
                leastDistanceToHit = distance;
                hitPlane = &plane;
            }
    }

    if (hitSphere) {
        Vec3f point = origin + (nRay * leastDistanceToHit);
        Vec3f N = GRY_VecNormalize(point - hitSphere->center);
        if (GRY_VecDot(nRay, N) > 0.f) { N = N * -1.f; }
        GRY_Material mat = hitSphere->material;

        Vec3f eRay = nRay;
        if (reflect < reflectionLimit && (hitSphere->material.reflect || hitSphere->material.refract)) {
            if (hitSphere->material.refract) {
                eRay = GRY_VecRefract(eRay, N, 1.f, hitSphere->material.refractIndex);
                if (hitSphere->material.reflect) { eRay = eRay * -1.f; }
            }
            if (hitSphere->material.reflect) {
                eRay = GRY_VecReflect(eRay, N);
            }
            Vec3f eOrigin = GRY_VecDot(eRay, N) < 0.f ? point - (N * 1e-3f) : point + (N * 1e-3f);
            if (castRay(eOrigin, eRay, color, reflect+1)) { mat.diffuseColor = color; }
        }
        color = blinnPhong(this, mat, N, point, origin, nRay);
    }

    else if (hitPlane) {
        Vec3f point = origin + (nRay * leastDistanceToHit);
        Vec3f N = hitPlane->n * (GRY_VecDot(nRay, hitPlane->n) > 0.f ? -1.f : 1.f);
        GRY_Material mat = hitPlane->material;

        Vec3f eRay = nRay;
        if (reflect < reflectionLimit && (hitPlane->material.reflect || hitPlane->material.refract)) {
            if (hitPlane->material.refract) {
                eRay = GRY_VecRefract(eRay, N, 1.f, hitPlane->material.refractIndex);
                if (hitPlane->material.reflect) { eRay = eRay * -1.f; }
            }
            if (hitPlane->material.reflect) {
                eRay = GRY_VecReflect(eRay, N);
            }
            Vec3f eOrigin = GRY_VecDot(eRay, N) < 0.f ? point - (N * 1e-3f) : point + (N * 1e-3f);
            if (castRay(eOrigin, eRay, color, reflect+1)) { mat.diffuseColor = color; }
        }

        color = blinnPhong(this, mat, N, point, origin, nRay);
    }
    
    return hitSphere || hitPlane;
}

bool Scene::castRay(const Vec3f& origin, const Vec3f& nRay, const float* withinDistance) const {
    float distance;
    for (auto& sphere : spheres) {
        if (rayIntersectSphere(sphere, nRay, origin, &distance)) {
            if (withinDistance && distance > *withinDistance) { continue; }
            return true;
        }
    }
    for (auto& plane : planes) {
        if (rayIntersectPlane(plane, nRay, origin, &distance)) {
            if (withinDistance && distance > *withinDistance) { continue; }
            return true;
        }
    }

    return false;
}
