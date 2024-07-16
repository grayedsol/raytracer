#include "Scene.hpp"
#include "BlinnPhong.hpp"
#include "Ray.hpp"

void Scene::drawScene(const GRY_View& view, GRY_Ppm& ppm) {
    GRY_Color color;
    GRY_Color ambient{0.0f, 0.0f, 0.0f, 1.0f};
    for (auto& light : lights) { ambient += (light.color * light.intensity) * 0.025f; }
    for (int i = 0; i < view.rays.size(); i++) {
        if (castRay(view.origin, view.rays.at(i), color)) {
            ppm.frameBuffer.at(i) = color + ambient;
        }
    }
}

bool Scene::castRay(const Vec3f &origin, const Vec3f &nRay, GRY_Color& color, int reflect) {
    float leastDistanceToHit = -1.0f;
    const Sphere* hitSphere = nullptr;
    const Plane* hitPlane = nullptr;

    for (auto& sphere : spheres) {
        float distance;
        if (rayIntersectSphere(sphere, nRay, origin, &distance) && 
            (distance < leastDistanceToHit || leastDistanceToHit < 0.0f && distance >= 0.0f)) {
            leastDistanceToHit = distance;
            hitSphere = &sphere;
        }
    }
    for (auto& plane : planes) {
        float distance;
        if (rayIntersectPlane(plane, nRay, origin, &distance) &&
            (distance < leastDistanceToHit || leastDistanceToHit < 0.0f && distance >= 0.0f)) {
                hitSphere = nullptr;
                leastDistanceToHit = distance;
                hitPlane = &plane;
            }
    }

    if (hitSphere) {
        Vec3f point = origin + (nRay * leastDistanceToHit);
        Vec3f N = GRY_VecNormalize(point - hitSphere->center);
        GRY_Material mat = hitSphere->material;
        if (hitSphere->material.refract && hitSphere->material.reflect && reflect < reflectionLimit) {
            Vec3f refractRay = GRY_VecRefract(nRay, N, 1.0f, hitSphere->material.refractIndex);
            Vec3f reflectRay = GRY_VecReflect(refractRay, N) * -1.0f;
            Vec3f reflectOrigin = GRY_VecDot(reflectRay, N) < 0 ? point - (N * 0.001f) : point + (N * 0.001f);

            if (castRay(reflectOrigin, reflectRay, color, reflect+1)) { mat.diffuseColor = color; }
        }
        else if (hitSphere->material.refract && reflect < reflectionLimit) {
            Vec3f refractRay = GRY_VecRefract(nRay, N, 1.0f, hitSphere->material.refractIndex);
            Vec3f refractOrigin = GRY_VecDot(refractRay, N) < 0 ? point - (N * 0.001f) : point + (N * 0.001f);

            if (castRay(refractOrigin, refractRay, color, reflect+1)) { mat.diffuseColor = color; }
        }
        else if (hitSphere->material.reflect && reflect < reflectionLimit) {
            Vec3f reflectRay = GRY_VecReflect(nRay, N);
            Vec3f reflectOrigin = GRY_VecDot(reflectRay, N) < 0 ? point - (N * 0.0001f) : point + (N * 0.0001f);

            if (castRay(reflectOrigin, reflectRay, color, reflect+1)) { mat.diffuseColor = color; }
        }
        color = blinnPhong(this, mat, N, point, origin, nRay);
    }

    else if (hitPlane) {
        Vec3f point = origin + (nRay * leastDistanceToHit);
        Vec3f N = hitPlane->n * (GRY_VecDot(nRay, hitPlane->n) > 0 ? -1.0f : 1.0f);
        GRY_Material mat = hitPlane->material;
        color = blinnPhong(this, mat, N, point, origin, nRay);
    }
    
    return hitSphere || hitPlane;
}

bool Scene::castRay(const Vec3f& origin, const Vec3f& nRay, const float* withinDistance) const {
    float distance;
    for (auto& sphere : spheres) {
        if (rayIntersectSphere(sphere, nRay, origin, &distance)) {
            if (withinDistance && distance > *withinDistance) { return false; }
            return true;
        }
    }
    for (auto& plane : planes) {
        if (rayIntersectPlane(plane, nRay, origin, &distance)) {
            if (withinDistance && distance > *withinDistance) { return false; }
            return true;
        }
    }

    return false;
}
