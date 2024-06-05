#include "Scene.hpp"

void Scene::drawScene(const Vec3f& origin, const std::vector<Vec3f>& rays, GRY_Ppm& ppm) {
    GRY_Color material;
    Vec3f point;
    for (int i = 0; i < ppm.height; i++) {
        for (int j = 0; j < ppm.width; j++) {
            if (rayIntersect(spheres, lights, origin, rays.at(i*ppm.width+j), point, material)) {
                ppm.frameBuffer.at(i*ppm.width+j) = material;
            }
        }
    }    
}