#pragma once
#include "../math/Vector3.hpp"
#include "../utils/Color.hpp"

class Light {
  public:
    Vector3 position;
    Color intensity;

    Light();
    Light(const Vector3& position, const Color& intensity);

    // Get direction from point to light
    Vector3 getDirection(const Vector3& point) const;

    // Get distance from point to light
    float getDistance(const Vector3& point) const;

    // Get light intensity at given point (for point lights, this is just the intensity)
    Color getIntensity(const Vector3& point) const;
};
