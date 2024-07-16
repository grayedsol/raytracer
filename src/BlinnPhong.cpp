#include "BlinnPhong.hpp"
#include <algorithm>
#include "Scene.hpp"

GRY_Color phong(const Scene* scene, const GRY_Material& material, const Vec3f& N, const Vec3f& point, const Vec3f& origin, const Vec3f& ray) {
    GRY_Color illumination = GRY_Black;
    GRY_Color specular = GRY_Black;

    /* Vector from point to origin (viewer) */
    Vec3f V = GRY_VecNormalize(origin - point);

    for (auto& light : scene->lights) {
        /* Vector from hit to light source */
        Vec3f L = GRY_VecNormalize(light.position - point);

        Vec3f shadowPoint = GRY_VecDot(L, N) < 0 ? point - N*0.01f : point + N*0.01f;
        float withinDistance = sqrtf(GRY_VecDistanceSq(shadowPoint, light.position));
        if (scene->castRay(shadowPoint, L, &withinDistance)) { continue; }

        /* Reflection of L on point */
        Vec3f R = N * (2 * std::max(0.0f, GRY_VecDot(L, N))) - L;

        /* Diffuse */
        illumination += light.color * std::max(0.0f, GRY_VecDot(L, N));
        /* Specular */
        specular += light.color * powf(std::max(0.0f, GRY_VecDot(R, V)), material.shine);
    }

    return (material.diffuseColor * illumination) + (material.specularColor * specular);
}

GRY_Color blinnPhong(const Scene* scene, const GRY_Material& material, const Vec3f& N, const Vec3f& point, const Vec3f& origin, const Vec3f& ray) {
    GRY_Color illumination = GRY_Black;
    GRY_Color specular = GRY_Black;

    for (auto& light : scene->lights) {
        /* Vector from hit to light source */
        Vec3f L = GRY_VecNormalize(light.position - point);

        Vec3f shadowPoint = GRY_VecDot(L, N) < 0 ? point - N*0.01f : point + N*0.01f;
        float withinDistance = sqrtf(GRY_VecDistanceSq(shadowPoint, light.position));
        if (scene->castRay(shadowPoint, L, &withinDistance)) { continue; }

        /* H as a point */
        Vec3f hPoint = (light.position + origin) * 0.5f;
        /* Halfway vector between light and origin from point */
        Vec3f H = GRY_VecNormalize(hPoint - point);

        /* Diffuse */
        illumination += light.color * std::max(0.0f, GRY_VecDot(L, N));
        /* Specular */
        specular += light.color * powf(std::max(0.0f, GRY_VecDot(N, H)), (material.shine * 4.0f));
    }

    return (material.diffuseColor * illumination) + (material.specularColor * specular);
}