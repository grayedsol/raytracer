#pragma once
#include <stdint.h>

struct GRY_Color {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;

    GRY_Color operator*(float scalar) const {
        return GRY_Color {
            (uint8_t)(r * scalar),
            (uint8_t)(g * scalar),
            (uint8_t)(b * scalar),
            a
        };
    }
};