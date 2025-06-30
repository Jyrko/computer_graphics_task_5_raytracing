#pragma once
#include <vector>

#include "Camera.hpp"
#include "Light.hpp"
#include "Sphere.hpp"

class Scene {
  public:
    std::vector<Sphere> spheres;
    std::vector<Light> lights;
    Color ambientLight;
    Color backgroundColor;

    Scene();

    void addSphere(const Sphere& sphere);
    void addLight(const Light& light);
    void setAmbientLight(const Color& ambient);
    void setBackgroundColor(const Color& background);

    struct HitInfo {
        bool hit;
        float t;
        Vector3 point;
        Vector3 normal;
        Material material;

        HitInfo() : hit(false), t(-1) {}
    };

    HitInfo raycast(const Ray& ray) const;

    // Create default scene for testing
    void createDefaultScene();
};
