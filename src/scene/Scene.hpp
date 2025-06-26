#pragma once
#include "Sphere.hpp"
#include "Light.hpp"
#include "Camera.hpp"
#include <vector>

class Scene {
public:
    std::vector<Sphere> spheres;
    std::vector<Light> lights;
    Color ambientLight;
    Color backgroundColor;
    
    Scene();
    
    // Scene setup
    void addSphere(const Sphere& sphere);
    void addLight(const Light& light);
    void setAmbientLight(const Color& ambient);
    void setBackgroundColor(const Color& background);
    
    // Ray tracing
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
