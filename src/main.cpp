#include <iostream>
#include "Scene.hpp"
#include "GRY_View.hpp"

const uint width = 1024;
const uint height = 768;
const uint distanceFromScreen = 512;

int main() {
    Scene scene;
    GRY_Ppm ppm(width, height);
    GRY_View view(ppm, distanceFromScreen);

    scene.spheres.push_back(Sphere{ Vec3f(2048, 500, 500), 400, GRY_Material{GRY_Color{.25f,.25f,1.0f,1.0f}} });
    scene.spheres.push_back(Sphere{ Vec3f(2048, 0, 0), 150, GRY_Material{GRY_Color{1.0f,.25f,.25f,1.0f}}  });
    scene.spheres.push_back(Sphere{ Vec3f(750, -200, -200), 50, GRY_Material{GRY_Color{.1f,.325f,.1f,1.0f}}  });
    scene.spheres.push_back(Sphere{ Vec3f(1000, 250, -400), 100, GRY_Material{GRY_Color{.9f,.9f,.325f,1.0f}} });
    scene.spheres.push_back(Sphere{ Vec3f(1000, 225, -250), 100, GRY_Material{GRY_Color{.1f,.1f,.5f,1.0f}} });
    scene.spheres.push_back(Sphere{ Vec3f(1000, -400, 300), 250, GRY_Material{GRY_Color{.325f,.25f,.5f,1.0f}} });

    scene.lights.push_back(Light{ Vec3f(500, 750, -750), 0.75f });
    scene.lights.push_back(Light{ Vec3f(500, 0, 2000), 0.75f });

    ppm.drawGradient();

    scene.drawScene(view, ppm);

    ppm.render();

    return 0;
}