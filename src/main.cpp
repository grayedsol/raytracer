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

    scene.spheres.push_back(Sphere{ Vec3f(500, -100, -100), 150, GRY_Material{GRY_Color{.0f,.0f,1.0f,1.0f}, GRY_White, 21.0f, false, true, 2.0f} });
    scene.spheres.push_back(Sphere{ Vec3f(2048, 0, 0), 150, GRY_Material{GRY_Color{1.0f,.25f,.25f,1.0f}}  });
    scene.spheres.push_back(Sphere{ Vec3f(750, -200, -200), 50, GRY_Material{GRY_Color{.1f,.7f,.1f,1.0f}}  });
    scene.spheres.push_back(Sphere{ Vec3f(1000, 250, -400), 100, GRY_Material{GRY_Color{.9f,.9f,.325f,1.0f}} });
    scene.spheres.push_back(Sphere{ Vec3f(1000, 225, -250), 100, GRY_Material{GRY_Color{.1f,.1f,.5f,1.0f}} });
    scene.spheres.push_back(Sphere{ Vec3f(1000, -400, 300), 250, GRY_Material{GRY_Color{.125f,.125f,.5f,1.0f}} });
    scene.spheres.push_back(Sphere{ Vec3f(1500, 200, -800), 350, GRY_Material{GRY_Color{.8f,.2f,.5f,1.0f}, GRY_White, 15.0f, true}  });
    scene.spheres.push_back(Sphere{ Vec3f(5000, 600, 300), 1500, GRY_Material{GRY_Color{.8f,.8f,.8f,1.0f}, GRY_Color{0.4f,0.4f,0.4f}, 3.0f} });

    scene.lights.push_back(Light{ Vec3f(250, 750, -1500), 0.75f/* , GRY_Color{0.1f,0.3f,1.0f} */});
    scene.lights.push_back(Light{ Vec3f(250, 0, 1500), 0.75f/* , GRY_Color{1.0f,0.3f,1.0f} */ });

    ppm.drawGradient();

    scene.drawScene(view, ppm);

    ppm.render();

    return 0;
}
