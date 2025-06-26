#include "Phong.hpp"
#include "../scene/Light.hpp"
#include <algorithm>
#include <cmath>

Color PhongShader::calculateColor(
    const Vector3& point,
    const Vector3& normal,
    const Vector3& viewDirection,
    const Material& material,
    const std::vector<Light>& lights,
    const Color& ambientLight
) {
    // Start with ambient reflection
    Color finalColor = material.ka * ambientLight;
    
    // Add contribution from each light
    for (const auto& light : lights) {
        Vector3 lightDirection = light.getDirection(point);
        Color lightIntensity = light.getIntensity(point);
        
        // Diffuse reflection
        float nDotL = std::max(0.0f, normal.dot(lightDirection));
        Color diffuse = material.kd * lightIntensity * nDotL;
        
        // Specular reflection
        Vector3 reflectionDirection = reflect(-lightDirection, normal);
        float vDotR = std::max(0.0f, viewDirection.dot(reflectionDirection));
        float specularFactor = std::pow(vDotR, material.m);
        Color specular = material.ks * lightIntensity * specularFactor;
        
        finalColor += diffuse + specular;
    }
    
    return finalColor;
}

Vector3 PhongShader::reflect(const Vector3& incident, const Vector3& normal) {
    return incident - 2.0f * incident.dot(normal) * normal;
}
