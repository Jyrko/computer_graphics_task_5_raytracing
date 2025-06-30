#include "Ray.hpp"

#include "Matrix4.hpp"

Ray::Ray() : origin(Vector3::zero()), direction(Vector3::forward()) {}

Ray::Ray(const Vector3& origin, const Vector3& direction)
    : origin(origin), direction(direction.normalized()) {}

Vector3 Ray::at(float t) const {
    return origin + direction * t;
}
