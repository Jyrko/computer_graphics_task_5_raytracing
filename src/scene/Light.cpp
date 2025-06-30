#include "Light.hpp"

Light::Light() : position(Vector3::zero()), intensity(Color::white()) {}

Light::Light(const Vector3& position, const Color& intensity)
    : position(position), intensity(intensity) {}

Vector3 Light::getDirection(const Vector3& point) const {
    return (position - point).normalized();
}

float Light::getDistance(const Vector3& point) const {
    return (position - point).length();
}

Color Light::getIntensity(const Vector3& point) const {
    return intensity;
}
