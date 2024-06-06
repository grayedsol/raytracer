#include "BlinnPhong.hpp"
#include <algorithm>
GRY_Color phongReflect(const std::vector<Light>& lights, const Sphere& sphere, const Vec3f& hit, const Vec3f& origin, const Vec3f& ray) {
    float illumination = 0.0f;
    float specular = 0.0f;
    const float lightConstant = 16.0f;
    //const Vec3f lightConstant(1.0f, 1.0f, 1.0f);
    /* Vector of the normal of the sphere at hit */
    Vec3f N = GRY_VecNormalize(hit - sphere.center);
    /* Vector from hit to origin (viewer) */
     Vec3f V = GRY_VecNormalize(origin - hit);
    for (auto& light : lights) {
        /* Vector from hit to light source */
        Vec3f L = GRY_VecNormalize(light.position - hit);
        /* Reflection of L on hit */
        Vec3f R = N * (2 * std::max(0.0f, GRY_VecDot(L, N))) - L;

        float diffuse = GRY_VecDot(L, N) * sphere.material.diffuse;
        if (diffuse <= 0.0f) { diffuse = 0.0f; }
        specular += powf(std::max(0.0f, GRY_VecDot(R, V)), 15.0f) * sphere.material.specular * light.intensity;
        //if (specular <= 0.0f) { specular = 0.0f; }

        illumination += (light.intensity * diffuse);
    }
    Vec3f color {
        sphere.material.color.r * illumination + specular,
        sphere.material.color.g * illumination + specular,
        sphere.material.color.b * illumination + specular
    };
    for (int i = 0; i < 3; i++) {
        if (color[i] > 255.0f) { color[i] = 255.0f; }
    }
    return GRY_Color {
        (uint8_t)color[0], (uint8_t)color[1], (uint8_t)color[2], 255
    };

    //return sphere.material.color * illumination;
}