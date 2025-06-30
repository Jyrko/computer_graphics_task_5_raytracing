#pragma once
#include "Vector3.hpp"

class Matrix4 {
  private:
    float m[4][4];

  public:
    Matrix4();
    Matrix4(const Matrix4& other);

    float* operator[](int row);
    const float* operator[](int row) const;

    Matrix4 operator*(const Matrix4& other) const;
    Vector3 operator*(const Vector3& vector) const;
    Vector3 transformVector(const Vector3& vector) const;
    Matrix4& operator*=(const Matrix4& other);

    static Matrix4 identity();
    static Matrix4 translation(const Vector3& translation);
    static Matrix4 rotationX(float angle);
    static Matrix4 rotationY(float angle);
    static Matrix4 rotationZ(float angle);
    static Matrix4 scale(const Vector3& scale);
    static Matrix4 lookAt(const Vector3& position, const Vector3& target, const Vector3& up);

    Matrix4 transpose() const;
    void setIdentity();

    void set(int row, int col, float value);
    float get(int row, int col) const;
};
