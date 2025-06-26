#include "Camera.hpp"
#include <cmath>

Camera::Camera() 
    : position(0, 0, -5), target(0, 0, 0), up(0, 1, 0), 
      fieldOfView(45.0f * M_PI / 180.0f), distance(5.0f), 
      rotationX(0), rotationY(0) {}

Camera::Camera(const Vector3& position, const Vector3& target, const Vector3& up, float fov)
    : position(position), target(target), up(up), fieldOfView(fov),
      distance((position - target).length()), rotationX(0), rotationY(0) {}

Matrix4 Camera::getViewMatrix() const {
    return Matrix4::lookAt(position, target, up);
}

Matrix4 Camera::getInverseViewMatrix() const {
    return getViewMatrix().inverse();
}

Ray Camera::getRay(int x, int y, int width, int height) const {
    // Calculate camera coordinate system
    Vector3 cZ = (target - position).normalized();
    Vector3 cX = up.cross(cZ).normalized();
    Vector3 cY = cZ.cross(cX).normalized();
    
    // Calculate image plane dimensions
    float cx = (width - 1) / 2.0f;
    float cy = (height - 1) / 2.0f;
    float d = width / (2.0f * std::tan(fieldOfView / 2.0f));
    
    // Calculate point on image plane
    float px = x - cx;
    float py = -(y - cy); // Flip Y coordinate
    
    // Create ray in camera space
    Vector3 rayDirection = px * cX + py * cY + d * cZ;
    rayDirection.normalize();
    
    return Ray(position, rayDirection);
}

void Camera::setDistance(float newDistance) {
    distance = newDistance;
    updatePosition();
}

void Camera::rotate(float deltaX, float deltaY) {
    rotationX += deltaX;
    rotationY += deltaY;
    
    // Clamp vertical rotation
    rotationX = std::max(-M_PI/2 + 0.1f, std::min(M_PI/2 - 0.1f, rotationX));
    
    updatePosition();
}

void Camera::updatePosition() {
    // Convert spherical coordinates to cartesian
    float x = distance * std::cos(rotationX) * std::sin(rotationY);
    float y = distance * std::sin(rotationX);
    float z = distance * std::cos(rotationX) * std::cos(rotationY);
    
    position = target + Vector3(x, y, z);
}
