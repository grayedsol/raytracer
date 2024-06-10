#pragma once
#include <stdint.h>

struct GRY_Color {
    float r;
    float g;
    float b;
    float a = 1.0f;

    GRY_Color operator*(float scalar) const {
        return GRY_Color{
            (r * scalar),
            (g * scalar),
            (b * scalar),
            a
        };
    }

    GRY_Color operator*(const GRY_Color& rhs) const {
        return GRY_Color{
            r * rhs.r,
            g * rhs.g,
            b * rhs.b,
            a
        };
    }

    void operator*=(const GRY_Color& rhs) {
        r *= rhs.r;
        g *= rhs.g;
        b *= rhs.b;
    }


    GRY_Color operator+(const GRY_Color& rhs) const {
        return GRY_Color{
            r + rhs.r,
            g + rhs.g,
            b + rhs.b,
            a
        };
    }

    void operator+=(const GRY_Color& rhs) {
        r += rhs.r;
        g += rhs.g;
        b += rhs.b;
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
