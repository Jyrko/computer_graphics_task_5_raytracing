#pragma once
#include "../math/Vector3.hpp"
#include "../scene/Scene.hpp"
#include "../utils/Color.hpp"

class PhongShader {
  public:
    // Calculate color using Phong illumination model
    static Color calculateColor(const Vector3& point,              // Point on surface
                                const Vector3& normal,             // Surface normal at point
                                const Vector3& viewDirection,      // Direction to camera
                                const Material& material,          // Surface material
                                const std::vector<Light>& lights,  // Scene lights
                                const Color& ambientLight          // Ambient light intensity
    );

  private:
    // Calculate reflection vector
    static Vector3 reflect(const Vector3& incident, const Vector3& normal);
};
