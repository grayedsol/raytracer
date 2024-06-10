#pragma once
#include "GRY_Color.hpp"

struct GRY_Material {
    GRY_Color color;
    float diffuse = 1.0f;
    float specular = .75f;
};