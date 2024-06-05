#pragma once
#include "GRY_Ppm.hpp"
#include "GRY_Vec.hpp"

struct GRY_View {
    std::vector<Vec3f> rays;
    Vec3f origin;

    GRY_View(const GRY_Ppm& ppm, const int distanceFromScreen, Vec3f origin = Vec3f{0,0,0}) :
        rays(ppm.width*ppm.height) {
        int halfWidth = ppm.width / 2; int halfHeight = ppm.height / 2;

        for (int i = 0; i < ppm.height; i++) {
            for (int j = 0; j < ppm.width; j++) {
                rays[i*ppm.width+j] = Vec3f(distanceFromScreen, halfHeight - i, j - halfWidth);
            }
        }

        for (int i = 0; i < ppm.width * ppm.height; i++) {
            rays[i] = GRY_VecNormalize(rays[i]);
        }
    }
};