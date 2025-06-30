#pragma once
#include "../math/Matrix4.hpp"
#include "../math/Ray.hpp"
#include "../math/Vector3.hpp"

class Camera {
  public:
    Vector3 position;
    Vector3 target;
    Vector3 up;
    float fieldOfView;  // In radians
    float distance;     // Distance from target for orbital camera
    float rotationX;    // Rotation around X axis
    float rotationY;    // Rotation around Y axis

    Camera();
    Camera(const Vector3& position, const Vector3& target, const Vector3& up, float fov);

    Matrix4 getViewMatrix() const;

    Ray getRay(int x, int y, int width, int height) const;

    void setDistance(float distance);
    void rotate(float deltaX, float deltaY);
    void updatePosition();
};
