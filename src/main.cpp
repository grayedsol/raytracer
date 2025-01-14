#include <iostream>
#include "Scene.hpp"
#include "GRY_View.hpp"

const unsigned int width = 1024;
const unsigned int height = 768;
const unsigned int distanceFromScreen = 512;

int main() {
    Scene scene;
    GRY_Ppm ppm(width, height);
    GRY_View view(ppm, distanceFromScreen);

    scene.spheres.push_back(Sphere{ Vec3f(1024, 0, 0), 75, GRY_Material{GRY_Color{1.f,.25f,.25f,1.f}}  });
    scene.spheres.push_back(Sphere{ Vec3f(1200, -300, -300), 75, GRY_Material{GRY_Color{.1f,.7f,.1f,1.f}}  });
    scene.spheres.push_back(Sphere{ Vec3f(1500, 250, -400), 100, GRY_Material{GRY_Color{.9f,.9f,.325f,1.f}} });
    scene.spheres.push_back(Sphere{ Vec3f(1500, 225, -250), 100, GRY_Material{GRY_Color{.1f,.1f,.5f,1.f}} });
    scene.spheres.push_back(Sphere{ Vec3f(1200, -200, -100), 250, GRY_Material{GRY_Color{.125f,.125f,.5f,1.f}, GRY_White, 15.f, false, true, 1.02f} });
    scene.spheres.push_back(Sphere{ Vec3f(2500, 200, 700), 450, GRY_Material{GRY_Color{.8f,.2f,.5f,1.f}, GRY_White, 15.f, true}  });
    scene.spheres.push_back(Sphere{ Vec3f(1600, 400, 50), 150, GRY_Material{GRY_Color{1.f,.5f,0.f,1.f}, GRY_White, 15.f} });
    scene.spheres.push_back(Sphere{ Vec3f(1500, 300, -130), 300, GRY_Material{GRY_Color{0.f,0.f,1.f,1.f}, GRY_White, 21.f, true, true, 1.02f} });

    scene.planes.push_back(Plane{ GRY_VecNormalize(Vec3f(0,-1,0)), 500, GRY_Material{GRY_Color{1.f,1.f,0.f,1.f}, GRY_White, 15.f, true} });
    scene.planes.push_back(Plane{ GRY_VecNormalize(Vec3f(0,1,0)), 5000, GRY_Material{GRY_Color{.4f,.8f,.8f,1.f}} });

    scene.lights.push_back(Light{ Vec3f(50, 1500, -300), .75f });
    scene.lights.push_back(Light{ Vec3f(50, 750, 1500), .75f });

    ppm.drawGradient();

    scene.drawScene(view, ppm);

    ppm.render();

    return 0;
}
