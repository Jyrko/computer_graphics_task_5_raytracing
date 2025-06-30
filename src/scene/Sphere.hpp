#pragma once
#include "../math/Vector3.hpp"
#include "../utils/Color.hpp"

struct Material {
    Color ka;  // Ambient reflection coefficients
    Color kd;  // Diffuse reflection coefficients
    Color ks;  // Specular reflection coefficients
    float m;   // Specular focus coefficient

    Material();
    Material(const Color& ka, const Color& kd, const Color& ks, float m);
};

class Sphere {
  public:
    Vector3 center;
    float radius;
    Material material;

    Sphere();
    Sphere(const Vector3& center, float radius, const Material& material);

    float intersect(const class Ray& ray) const;

    Vector3 getNormal(const Vector3& point) const;
};
