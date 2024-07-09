#include "Scene.hpp"
#include "BlinnPhong.hpp"

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

    for (auto& sphere : spheres) {
        float distance;
        if (rayIntersectSphere(sphere, nRay, origin, &distance) && 
            (distance < leastDistanceToHit || leastDistanceToHit < 0.0f)) {
            leastDistanceToHit = distance;
            hitSphere = &sphere;
        }
    }

    if (hitSphere) {
        Vec3f point = origin + (nRay * leastDistanceToHit);
        Vec3f N = GRY_VecNormalize(point - hitSphere->center);
        GRY_Material mat = hitSphere->material;
        if (hitSphere->material.reflect && reflect < reflectionLimit) {
            Vec3f reflectRay = nRay + (N * GRY_VecDot(nRay, N) * -2.0f);
            Vec3f reflectOrigin = GRY_VecDot(reflectRay, N) < 0 ? point - (N * 0.0001f) : point + (N * 0.0001f);

            if (castRay(reflectOrigin, reflectRay, color, reflect+1)) { mat.diffuseColor = color; }
        }
        color = blinnPhong(this, mat, N, point, origin, nRay);
    }
    
    return hitSphere;
}

bool Scene::castRay(const Vec3f& origin, const Vec3f& nRay) const {
    for (auto& sphere : spheres) {
        if (rayIntersectSphere(sphere, nRay, origin)) { return true; }
    }
    return false;
}
