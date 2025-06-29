#include "Ray.hpp"

#include "Matrix4.hpp"

Ray::Ray() : origin(Vector3::zero()), direction(Vector3::forward()) {}

Ray::Ray(const Vector3& origin, const Vector3& direction)
    : origin(origin), direction(direction.normalized()) {}

Vector3 Ray::at(float t) const {
    return origin + direction * t;
}

Ray Ray::transform(const Matrix4& matrix) const {
    Vector3 newOrigin = matrix * origin;
    Vector3 newDirection = matrix.transformVector(direction);
    return Ray(newOrigin, newDirection);
}
