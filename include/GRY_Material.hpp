#pragma once
#include "GRY_Color.hpp"

struct GRY_Material {
    GRY_Color diffuseColor;
    GRY_Color specularColor = GRY_White;
    float shine = 15.0f;
    bool reflect = false;
    bool refract = false;
    float refractIndex = 1.0f;
};