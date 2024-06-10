#pragma once
#include <stdint.h>

struct GRY_Color {
    float r;
    float g;
    float b;
    float a;

    GRY_Color operator*(float scalar) const {
        return GRY_Color {
            (r * scalar),
            (g * scalar),
            (b * scalar),
            a
        };
    }

    /**
     * @brief Map to 0.0f - 1.0f range.
     * 
     * @param colors Array of colors.
     * @param count Size of the array.
     */
    static void mapToRange(GRY_Color colors[], unsigned int count);
};

extern GRY_Color GRY_Black;
extern GRY_Color GRY_White;
extern GRY_Color GRY_Blue;
extern GRY_Color GRY_Red;
extern GRY_Color GRY_Green;
