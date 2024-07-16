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

    scene.spheres.push_back(Sphere{ Vec3f(2048, 0, 0), 150, GRY_Material{GRY_Color{1.f,.25f,.25f,1.f}}  });
    scene.spheres.push_back(Sphere{ Vec3f(750, -200, -200), 50, GRY_Material{GRY_Color{.1f,.7f,.1f,1.f}}  });
    scene.spheres.push_back(Sphere{ Vec3f(1000, 250, -400), 100, GRY_Material{GRY_Color{.9f,.9f,.325f,1.f}} });
    scene.spheres.push_back(Sphere{ Vec3f(1000, 225, -250), 100, GRY_Material{GRY_Color{.1f,.1f,.5f,1.f}} });
    scene.spheres.push_back(Sphere{ Vec3f(1000, -400, 300), 250, GRY_Material{GRY_Color{.125f,.125f,.5f,1.f}} });
    scene.spheres.push_back(Sphere{ Vec3f(1500, 200, -800), 350, GRY_Material{GRY_Color{.8f,.2f,.5f,1.f}, GRY_White, 15.f, true}  });
    scene.spheres.push_back(Sphere{ Vec3f(3000, 1250, 500), 500, GRY_Material{GRY_Color{1.f,.5f,0.f,1.f}, GRY_White, 15.f} });
    scene.spheres.push_back(Sphere{ Vec3f(100, 0, 0), 40, GRY_Material{GRY_Color{0.f,0.f,1.f,1.f}, GRY_White, 21.f, true, true, 1.05f} });

    scene.planes.push_back(Plane{ Vec3f(0,-1,0), 1000, GRY_Material{GRY_Color{1.f,1.f,0.f,1.f}} });
    scene.planes.push_back(Plane{ Vec3f(0,1,0), 2500, GRY_Material{GRY_Color{1.f,.25f,.25f,1.f}} });
    scene.planes.push_back(Plane{ Vec3f(-1,0,0), 5000, GRY_Material{GRY_Color{.75f,0.f,.75f,1.f}} });
    scene.planes.push_back(Plane{ Vec3f(1,0,0), 5000, GRY_Material{GRY_Color{0.f,1.f,1.f,1.f}} });
    scene.planes.push_back(Plane{ Vec3f(0,0,1), 2000, GRY_Material{GRY_Color{.25f,.75f,.25f,1.f}} });
    scene.planes.push_back(Plane{ Vec3f(0,0,-1), 2000, GRY_Material{GRY_Color{.25f,.25f,.75f,1.f}} });


    scene.lights.push_back(Light{ Vec3f(0, 750, -1500), .75f /* , GRY_Color{0.1f,0.3f,1.f} */});
    scene.lights.push_back(Light{ Vec3f(0, 450, 1500), .75f /* , GRY_Color{1.f,0.3f,1.f} */ });

    ppm.drawGradient();

    scene.drawScene(view, ppm);

    ppm.render();

    return 0;
}
