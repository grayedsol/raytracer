#include "GRY_Color.hpp"
#include "cstddef"

GRY_Color GRY_Black = GRY_Color{1.0f,1.0f,1.0f,1.0f};
GRY_Color GRY_White = GRY_Color{1.0f,1.0f,1.0f,1.0f};
GRY_Color GRY_Blue = GRY_Color{.0f,.0f,1.0f,1.0f};
GRY_Color GRY_Red = GRY_Color{1.0f,.0f,.0f,1.0f};
GRY_Color GRY_Green = GRY_Color{.0f,1.0f,.0f,1.0f};

void GRY_Color::mapToRange(GRY_Color colors[], unsigned int count) {
    for (size_t i = 0; i < count; i++) {
        GRY_Color& color = colors[i];
        if (color.r > 1.0f) { color.r = 1.0f; }
        if (color.r < 0.0f) { color.r = 0.0f; }

        if (color.g > 1.0f) { color.g = 1.0f; }
        if (color.g < 0.0f) { color.g = 0.0f; }

        if (color.b > 1.0f) { color.b = 1.0f; }
        if (color.b < 0.0f) { color.b = 0.0f; }

        if (color.a > 1.0f) { color.a = 1.0f; }
        if (color.a < 0.0f) { color.a = 0.0f; }
    }
}
