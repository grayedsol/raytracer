#include <iostream>
#include <fstream>
#include <vector>
#include "gryvec.hpp"

const uint width = 1024;
const uint height = 768;

void render() {
    std::vector<Vec3f> frameBuffer(width * height);

    for (uint i = 0; i < height; i++) {
        for (uint j = 0; j < width; j++) {
            frameBuffer[i*width+j] = Vec3f(j/(float)width, i/(float)height, 0);
        }
    }

    std::ofstream ofs;
    ofs.open("./out.ppm");
    ofs << "P6\n" << width << " " << height << "\n255\n";
    for (uint i = 0; i < width * height; i++) {
        for (uint j = 0; j < 3; j++) {
            ofs << (char)(255 * frameBuffer[i][j]);
        }
    }
    ofs.close();
}

int main() {
    render();
    return 0;
}