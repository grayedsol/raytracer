#include "Scene.hpp"

void Scene::drawScene(const GRY_View& view, GRY_Ppm& ppm) {
    GRY_Color color;
    Vec3f point;
    for (int i = 0; i < view.rays.size(); i++) {
        if (rayIntersect(spheres, lights, view.origin, view.rays.at(i), point, color)) {
            ppm.frameBuffer.at(i) = color;
        }
    }
}