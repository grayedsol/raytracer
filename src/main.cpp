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

    scene.spheres.push_back(Sphere{ Vec3f(2048, 500, 500), 400, GRY_Color{0,0,255,255} });
    scene.spheres.push_back(Sphere{ Vec3f(2048, 150, 150), 150, GRY_Color{0,128,128,255}  });
    scene.spheres.push_back(Sphere{ Vec3f(1500, 500, 500), 50, GRY_Color{128,128,0,255}  });
    scene.spheres.push_back(Sphere{ Vec3f(750, -200, -200), 50, GRY_Color{26,100,26,255}  });
    scene.spheres.push_back(Sphere{ Vec3f(1000, 250, -400), 100, GRY_Color{230,230,100,255} });
    scene.spheres.push_back(Sphere{ Vec3f(1000, 225, -250), 100, GRY_Color{26,0,128,255} });
    scene.spheres.push_back(Sphere{ Vec3f(1000, -400, 300), 300, GRY_Color{100,64,128,255} });

    scene.lights.push_back(LightSource{ Vec3f(1000, 0, 0), 1.0f });

    ppm.drawGradient();

    scene.drawScene(view.origin, view.rays, ppm);

    ppm.render();

    return 0;
}