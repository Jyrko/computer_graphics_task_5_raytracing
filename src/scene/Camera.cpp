#include "Camera.hpp"

#include <algorithm>
#include <cmath>

Camera::Camera()
    : position(0, 0, -5),
      target(0, 0, 0),
      up(0, 1, 0),
      fieldOfView(45.0f * M_PI / 180.0f),
      distance(5.0f),
      rotationX(0),
      rotationY(0) {}

Camera::Camera(const Vector3& position, const Vector3& target, const Vector3& up, float fov)
    : position(position),
      target(target),
      up(up),
      fieldOfView(fov),
      distance((position - target).length()),
      rotationX(0),
      rotationY(0) {}

Matrix4 Camera::getViewMatrix() const {
    return Matrix4::lookAt(position, target, up);
}

Ray Camera::getRay(int x, int y, int width, int height) const {
    Vector3 cZ = (target - position).normalized();
    Vector3 cX = up.cross(cZ).normalized();
    Vector3 cY = cZ.cross(cX).normalized();

    // Calculate image plane center and distance (Section 4.1)
    float cx = (width - 1) / 2.0f;
    float cy = (height - 1) / 2.0f;
    float d = (width / 2.0f) * std::cos(fieldOfView / 2.0f) / std::sin(fieldOfView / 2.0f);

    Vector3 pPrime = Vector3(0, 0, 0);

    Vector3 q = Vector3(x - cx, -y + cy, d);  // q = [x-cx, -(y-cy), d]^T

    Vector3 vPrime = (q - pPrime).normalized();  // v' = (q - p') / ||q - p'||

    // Transform to world coordinates using camera basis vectors
    Vector3 rayDirection = vPrime.x * cX + vPrime.y * cY + vPrime.z * cZ; // v = M^(-1) * v'

    return Ray(position, rayDirection);
}

void Camera::setDistance(float newDistance) {
    distance = newDistance;
    updatePosition();
}

void Camera::rotate(float deltaX, float deltaY) {
    rotationX += deltaX;
    rotationY += deltaY;

    rotationX =
        std::max(-float(M_PI) / 2.0f + 0.1f, std::min(float(M_PI) / 2.0f - 0.1f, rotationX));

    updatePosition();
}

void Camera::updatePosition() {
    // Convert spherical coordinates to cartesian
    float x = distance * std::cos(rotationX) * std::sin(rotationY);
    float y = distance * std::sin(rotationX);
    float z = distance * std::cos(rotationX) * std::cos(rotationY);

    position = target + Vector3(x, y, z);
}
