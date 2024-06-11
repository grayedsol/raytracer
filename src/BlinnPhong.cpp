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
        /* Reflection of L on point */
        Vec3f R = N * (2 * std::max(0.0f, GRY_VecDot(L, N))) - L;

        GRY_Color diffuse = material.diffuseColor * std::max(0.0f, GRY_VecDot(L, N));
        specular += material.specularColor * light.color * powf(std::max(0.0f, GRY_VecDot(R, V)), material.shine);

        illumination += (diffuse * light.color);
    }

    return (material.diffuseColor * illumination) + specular;
}

GRY_Color blinnPhong(const Scene* scene, const GRY_Material& material, const Vec3f& N, const Vec3f& point, const Vec3f& origin, const Vec3f& ray) {
    GRY_Color illumination = GRY_Black;
    GRY_Color specular = GRY_Black;
    GRY_Color ambient{0.0f,0.0f,0.0f,1.0f};
    for (auto& light : scene->lights) {
        ambient += (light.color * light.intensity) * 0.025f;
        /* Vector from hit to light source */
        Vec3f L = GRY_VecNormalize(light.position - point);

        Vec3f shadowPoint = GRY_VecDot(L, N) < 0 ? point - N*0.001f : point + N*0.001f;
        if (scene->castRay(shadowPoint, L)) { 
            continue;
        }

        /* H as a point */
        Vec3f hPoint = (light.position + origin) * 0.5f;
        /* Halfway vector between light and origin from point */
        Vec3f H = GRY_VecNormalize(hPoint - point);

        GRY_Color diffuse = material.diffuseColor * std::max(0.0f, GRY_VecDot(L, N));
        specular += material.specularColor * light.color * powf(std::max(0.0f, GRY_VecDot(N, H)), (material.shine * 4.0f));

        illumination += diffuse * light.color;
    }

    return (material.diffuseColor * illumination) + specular + ambient;
}