#pragma once
#include <cmath>

class Vector3 {
public:
    float x, y, z;

    Vector3();
    Vector3(float x, float y, float z);
    Vector3(const Vector3& other);

    // Basic operations
    Vector3 operator+(const Vector3& other) const;
    Vector3 operator-(const Vector3& other) const;
    Vector3 operator*(float scalar) const;
    Vector3 operator/(float scalar) const;
    Vector3& operator+=(const Vector3& other);
    Vector3& operator-=(const Vector3& other);
    Vector3& operator*=(float scalar);
    Vector3& operator/=(float scalar);

    // Vector operations
    float dot(const Vector3& other) const;
    Vector3 cross(const Vector3& other) const;
    float length() const;
    float lengthSquared() const;
    Vector3 normalized() const;
    void normalize();

    // Static methods
    static Vector3 zero();
    static Vector3 one();
    static Vector3 up();
    static Vector3 right();
    static Vector3 forward();
};

// Global operators
Vector3 operator*(float scalar, const Vector3& vector);
