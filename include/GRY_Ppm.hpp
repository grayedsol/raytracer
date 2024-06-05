#pragma once
#include <vector>
#include <fstream>
#include "GRY_Color.hpp"

struct GRY_Ppm {
    const unsigned int width;
    const unsigned int height;
    std::vector<GRY_Color> frameBuffer;

    GRY_Ppm(const unsigned int width, const unsigned int height) : width(width), height(height), frameBuffer(width*height) {}

    void render() {
        std::ofstream image("image.ppm", std::ios::binary);
        image << "P6\n" << width << " " << height << "\n255\n";
        for (auto& pixel : frameBuffer) { image << pixel.r << pixel.g << pixel.b; }
        image.close();
    }

    void drawGradient() {
        for (uint i = 0; i < height; i++) {
            for (uint j = 0; j < width; j++) {
                frameBuffer[i*width+j] = GRY_Color{
                    (uint8_t)(i/(float)height*255),
                    (uint8_t)(j/(float)width*255),
                    0
                };
            }
        }
    }
};

