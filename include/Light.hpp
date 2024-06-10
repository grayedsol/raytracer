#pragma once
#include "GRY_Vec.hpp"
#include "GRY_Color.hpp"

struct Light {
    Vec3f position;
    float intensity;
    GRY_Color color = GRY_White;
};