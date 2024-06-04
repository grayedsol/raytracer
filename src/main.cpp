#include <iostream>
#include <fstream>
#include <vector>
#include "gryvec.hpp"
#include "sphere.hpp"

const uint width = 1024;
const uint height = 768;
const uint imgSize = width * height;
const uint distanceFromScreen = 512;

void createRayVecs(Vec3f rayVecs[imgSize], const Vec3f& origin = Vec3f(0,0,0)) {
    int halfWidth = width / 2; int halfHeight = height / 2;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            rayVecs[i*width+j] = Vec3f(distanceFromScreen, halfHeight - i, j - halfWidth);
        }
    }

    for (int i = 0; i < imgSize; i++) {
        rayVecs[i] = GRY_VecNormalize(rayVecs[i]);
    }
}

void drawGradient(Vec3f frameBuffer[imgSize]) {
    for (uint i = 0; i < height; i++) {
        for (uint j = 0; j < width; j++) {
            frameBuffer[i*width+j] = Vec3f(i/(float)height, j/(float)width, 0);
        }
    }
}

void drawSpheres(const std::vector<Sphere>& spheres, const Vec3f& origin, const std::vector<Vec3f>& rays, std::vector<Vec3f>& frameBuffer) {
    Vec3f material;
    Vec3f point;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (rayIntersect(spheres, origin, rays.at(i*width+j), point, material)) {
                frameBuffer.at(i*width+j) = material;
            }
        }
    }
}

void render(Vec3f frameBuffer[imgSize]) {
    std::ofstream image("image.ppm", std::ios::out | std::ios::binary);
    image << "P6\n" << width << " " << height << "\n255\n";
    for (uint i = 0; i < imgSize; i++) {
        for (uint j = 0; j < 3; j++) {
            image << (char)(255 * frameBuffer[i][j]);
        }
    }
    image.close();
}

int main() {
    std::vector<Vec3f> frameBuffer(imgSize);
    std::vector<Vec3f> rayVecs(imgSize);
    std::vector<Sphere> spheres;

    Vec3f origin(0,0,0);
    spheres.push_back(Sphere{ Vec3f(2048, 500, 500), 400, Vec3f(0, 0, 1) });
    spheres.push_back(Sphere{ Vec3f(2048, 150, 150), 150, Vec3f(0, 0.5, 0.5) });
    spheres.push_back(Sphere{ Vec3f(1500, 500, 500), 50, Vec3f(0.5, 0.5, 0) });
    spheres.push_back(Sphere{ Vec3f(750, -200, -200), 50, Vec3f(0.1, 0.4, 0.1) });
    spheres.push_back(Sphere{ Vec3f(1000, 250, -400), 100, Vec3f(0.9, 0.9, 0.4) });
    spheres.push_back(Sphere{ Vec3f(1000, 225, -250), 100, Vec3f(0.1, 0, 0.5) });
    spheres.push_back(Sphere{ Vec3f(1000, -400, 300), 300, Vec3f(0.4, 0.25, 0.5) });

    createRayVecs(rayVecs.data(), origin);

    drawGradient(frameBuffer.data());

    drawSpheres(spheres, origin, rayVecs, frameBuffer);

    Vec3f& debugVec = frameBuffer.at(393214);
    float f = GRY_VecLengthSq(debugVec);

    render(frameBuffer.data());

    return 0;
}