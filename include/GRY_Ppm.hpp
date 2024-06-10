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
        GRY_Color::mapToRange(frameBuffer.data(), frameBuffer.size());
        for (auto& pixel : frameBuffer) { image <<
            (uint8_t)(pixel.r * 255.0f) <<
            (uint8_t)(pixel.g * 255.0f) <<
            (uint8_t)(pixel.b * 255.0f);
        }
        image.close();
    }

    void drawGradient() {
        for (uint i = 0; i < height; i++) {
            for (uint j = 0; j < width; j++) {
                frameBuffer[i*width+j] = GRY_Color{
                    i/(float)height,
                    j/(float)width,
                    0
                };
            }
        }
    }
};

