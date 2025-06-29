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

    // Ray-sphere intersection
    // Returns t value of intersection, or -1 if no intersection
    float intersect(const class Ray& ray) const;

    // Get normal at point on sphere surface
    Vector3 getNormal(const Vector3& point) const;
};
