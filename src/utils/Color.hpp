#pragma once
#include <cstdint>

struct Color {
    float r, g, b;
    
    Color();
    Color(float r, float g, float b);
    Color(const Color& other);
    
    // Arithmetic operations
    Color operator+(const Color& other) const;
    Color operator*(float scalar) const;
    Color operator*(const Color& other) const; // Component-wise multiplication
    Color& operator+=(const Color& other);
    Color& operator*=(float scalar);
    
    // Utility methods
    Color clamp() const;
    uint32_t toRGB() const;
    
    // Common colors
    static Color black();
    static Color white();
    static Color red();
    static Color green();
    static Color blue();
};

// Global operators
Color operator*(float scalar, const Color& color);
