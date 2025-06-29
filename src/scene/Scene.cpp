#include "Scene.hpp"

#include <limits>

Scene::Scene() : ambientLight(0.1f, 0.1f, 0.1f), backgroundColor(0.2f, 0.2f, 0.2f) {}

void Scene::addSphere(const Sphere& sphere) {
    spheres.push_back(sphere);
}

void Scene::addLight(const Light& light) {
    lights.push_back(light);
}

void Scene::setAmbientLight(const Color& ambient) {
    ambientLight = ambient;
}

void Scene::setBackgroundColor(const Color& background) {
    backgroundColor = background;
}

Scene::HitInfo Scene::raycast(const Ray& ray) const {
    HitInfo closestHit;
    float closestT = std::numeric_limits<float>::max();

    for (const auto& sphere : spheres) {
        float t = sphere.intersect(ray);
        if (t > 0 && t < closestT) {
            closestT = t;
            closestHit.hit = true;
            closestHit.t = t;
            closestHit.point = ray.at(t);
            closestHit.normal = sphere.getNormal(closestHit.point);
            closestHit.material = sphere.material;
        }
    }

    return closestHit;
}

void Scene::createDefaultScene() {
    // Clear existing scene
    spheres.clear();
    lights.clear();

    // Create some spheres with different materials
    Material redMaterial(Color(0.1f, 0.0f, 0.0f),  // ka - ambient
                         Color(0.7f, 0.2f, 0.2f),  // kd - diffuse
                         Color(1.0f, 1.0f, 1.0f),  // ks - specular
                         50.0f                     // m - specular focus
    );

    Material greenMaterial(Color(0.0f, 0.1f, 0.0f), Color(0.2f, 0.7f, 0.2f),
                           Color(1.0f, 1.0f, 1.0f), 30.0f);

    Material blueMaterial(Color(0.0f, 0.0f, 0.1f), Color(0.2f, 0.2f, 0.7f), Color(1.0f, 1.0f, 1.0f),
                          80.0f);

    // Add spheres
    addSphere(Sphere(Vector3(-2, 0, 0), 1.0f, redMaterial));
    addSphere(Sphere(Vector3(0, 0, 0), 1.0f, greenMaterial));
    addSphere(Sphere(Vector3(2, 0, 0), 1.0f, blueMaterial));

    // Add a larger sphere in the back
    Material yellowMaterial(Color(0.1f, 0.1f, 0.0f), Color(0.8f, 0.8f, 0.2f),
                            Color(1.0f, 1.0f, 1.0f), 20.0f);
    addSphere(Sphere(Vector3(0, -2, 3), 1.5f, yellowMaterial));

    // Add white point light
    addLight(Light(Vector3(5, 5, -5), Color::white()));

    // Set ambient light
    setAmbientLight(Color(0.1f, 0.1f, 0.1f));
}
