/**
 * @file BlinnPhong.hpp
 * @author Grayedsol (grayedsol@gmail.com)
 * @brief Phong and BlinnPhong illumination functions.
 * @copyright Copyright (c) 2024
 */
#pragma once
#include "Sphere.hpp"

class Scene;

/**
 * @brief Calculates the RGB value of a surface using the Phong illumination model.
 * 
 * @param scene Scene data.
 * @param material Material of the surface.
 * @param N Normalized normal of the surface.
 * @param point The coordinates of the point on the surface to be calculated.
 * @param origin Origin point of ray.
 * @param ray Normalized direction ray.
 * @return Color of the surface.
 */
GRY_Color phong(const Scene* scene, const GRY_Material& material, const Vec3f& N, const Vec3f& point, const Vec3f& origin, const Vec3f& ray);

/**
 * @brief Calculates the RGB value of a surface using the BlinnPhong illumination model.
 * 
 * @param scene Scene data.
 * @param material Material of the surface.
 * @param N Normalized normal of the surface.
 * @param point The coordinates of the point on the surface to be calculated.
 * @param origin Origin point of ray.
 * @param ray Normalized direction ray.
 * @return Color of the surface.
 */
GRY_Color blinnPhong(const Scene* scene, const GRY_Material& material, const Vec3f& N, const Vec3f& point, const Vec3f& origin, const Vec3f& ray);