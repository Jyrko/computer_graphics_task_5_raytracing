#include "Sphere.hpp"

#include <cmath>

#include "../math/Ray.hpp"

Material::Material() : ka(Color::black()), kd(Color::white()), ks(Color::white()), m(10.0f) {}

Material::Material(const Color& ka, const Color& kd, const Color& ks, float m)
    : ka(ka), kd(kd), ks(ks), m(m) {}

Sphere::Sphere() : center(Vector3::zero()), radius(1.0f), material() {}

Sphere::Sphere(const Vector3& center, float radius, const Material& material)
    : center(center), radius(radius), material(material) {}

float Sphere::intersect(const Ray& ray) const {
    Vector3 oc = ray.origin - center;

    float a = ray.direction.dot(ray.direction);
    float b = 2.0f * oc.dot(ray.direction);
    float c = oc.dot(oc) - radius * radius;

    float discriminant = b * b - 4 * a * c;

    if (discriminant < 0) {
        return -1.0f;  // No intersection
    }

    float sqrt_discriminant = std::sqrt(discriminant);
    float t1 = (-b - sqrt_discriminant) / (2.0f * a);
    float t2 = (-b + sqrt_discriminant) / (2.0f * a);

    // Return the closest positive intersection
    if (t1 > 0) {
        return t1;
    } else if (t2 > 0) {
        return t2;
    }

    return -1.0f;  // No positive intersection
}

Vector3 Sphere::getNormal(const Vector3& point) const {
    return (point - center).normalized();
}
