#include "BlinnPhong.hpp"
#include <algorithm>

GRY_Color phong(const std::vector<Light>& lights, const GRY_Material& material, const Vec3f& N, const Vec3f& point, const Vec3f& origin, const Vec3f& ray) {
    float illumination = 0.0f;
    float specular = 0.0f;
    const float lightConstant = 16.0f;
    /* Vector from point to origin (viewer) */
    Vec3f V = GRY_VecNormalize(origin - point);

    for (auto& light : lights) {
        /* Vector from hit to light source */
        Vec3f L = GRY_VecNormalize(light.position - point);
        /* Reflection of L on point */
        Vec3f R = N * (2 * std::max(0.0f, GRY_VecDot(L, N))) - L;

        float diffuse = std::max(0.0f, GRY_VecDot(L, N) * material.diffuse);
        if (diffuse <= 0.0f) { diffuse = 0.0f; }
        specular += powf(std::max(0.0f, GRY_VecDot(R, V)), 15.0f) * material.specular * light.intensity;

        illumination += (light.intensity * diffuse);
    }
    Vec3f color {
        material.color.r * illumination + specular,
        material.color.g * illumination + specular,
        material.color.b * illumination + specular
    };
    for (int i = 0; i < 3; i++) {
        if (color[i] > 255.0f) { color[i] = 255.0f; }
    }
    return GRY_Color {
        (uint8_t)color[0], (uint8_t)color[1], (uint8_t)color[2], 255
    };
}

GRY_Color blinnPhong(const std::vector<Light>& lights, const GRY_Material& material, const Vec3f& N, const Vec3f& point, const Vec3f& origin, const Vec3f& ray) {
    float illumination = 0.0f;
    float specular = 0.0f;
    const float lightConstant = 16.0f;

    for (auto& light : lights) {
        /* Vector from hit to light source */
        Vec3f L = GRY_VecNormalize(light.position - point);
        /* H as a point */
        Vec3f hPoint = (light.position + origin) * 0.5f;
        /* Halfway vector between light and origin from point */
        Vec3f H = GRY_VecNormalize(hPoint - point);

        float diffuse = std::max(0.0f, GRY_VecDot(L, N) * material.diffuse);
        specular += powf(std::max(0.0f, GRY_VecDot(N, H)), 60.0f) * material.specular * light.intensity;

        illumination += light.intensity * diffuse;
    }
    Vec3f color {
        material.color.r * illumination + specular,
        material.color.g * illumination + specular,
        material.color.b * illumination + specular
    };
    for (int i = 0; i < 3; i++) {
        if (color[i] > 255.0f) { color[i] = 255.0f; }
    }
    return GRY_Color {
        (uint8_t)color[0], (uint8_t)color[1], (uint8_t)color[2], 255
    };
}