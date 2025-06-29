#pragma once
#include "Vector3.hpp"

class Matrix4 {
  private:
    float m[4][4];

  public:
    Matrix4();
    Matrix4(const Matrix4& other);

    // Access operators
    float* operator[](int row);
    const float* operator[](int row) const;

    // Matrix operations
    Matrix4 operator*(const Matrix4& other) const;
    Vector3 operator*(const Vector3& vector) const;        // Transform point (w=1)
    Vector3 transformVector(const Vector3& vector) const;  // Transform vector (w=0)
    Matrix4& operator*=(const Matrix4& other);

    // Matrix creation methods (these need to be implemented manually)
    static Matrix4 identity();
    static Matrix4 translation(const Vector3& translation);
    static Matrix4 rotationX(float angle);
    static Matrix4 rotationY(float angle);
    static Matrix4 rotationZ(float angle);
    static Matrix4 scale(const Vector3& scale);
    static Matrix4 lookAt(const Vector3& position, const Vector3& target, const Vector3& up);

    // Matrix utilities
    Matrix4 inverse() const;
    Matrix4 transpose() const;
    void setIdentity();

    // Direct element access
    void set(int row, int col, float value);
    float get(int row, int col) const;
};
