#include "Scene.hpp"
#include "BlinnPhong.hpp"

void Scene::drawScene(const GRY_View& view, GRY_Ppm& ppm) {
    GRY_Color color;
    for (int i = 0; i < view.rays.size(); i++) {
        if (castRay(view.origin, view.rays.at(i), color)) {
            ppm.frameBuffer.at(i) = color;
        }
    }
}

bool Scene::castRay(const Vec3f &origin, const Vec3f &nRay, GRY_Color& color) {
    float leastDistanceToHit = -1.0f;
    const Sphere* hitSphere = nullptr;
    for (auto& sphere : spheres) {
        float distance;
        if (rayIntersectSphere(sphere, nRay, &distance) && 
            (distance < leastDistanceToHit || leastDistanceToHit < 0.0f)) {
            leastDistanceToHit = distance;
            hitSphere = &sphere;
        }
    }
    if (hitSphere) {
        Vec3f point = origin + (nRay * leastDistanceToHit);
        Vec3f N = GRY_VecNormalize(point - hitSphere->center);
        color = blinnPhong(this, hitSphere->material, N, point, origin, nRay);
    }
    return hitSphere;
}

bool Scene::castRay(const Vec3f& origin, const Vec3f& nRay) const {
    for (auto& sphere : spheres) {
        if (rayIntersectSphere(sphere, nRay, origin)) { return true; }
    }
    return false;
}
