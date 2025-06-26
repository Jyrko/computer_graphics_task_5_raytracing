#include "Matrix4.hpp"
#include <cstring>
#include <cmath>

Matrix4::Matrix4() {
    setIdentity();
}

Matrix4::Matrix4(const Matrix4& other) {
    std::memcpy(m, other.m, sizeof(m));
}

float* Matrix4::operator[](int row) {
    return m[row];
}

const float* Matrix4::operator[](int row) const {
    return m[row];
}

Matrix4 Matrix4::operator*(const Matrix4& other) const {
    Matrix4 result;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result.m[i][j] = 0;
            for (int k = 0; k < 4; k++) {
                result.m[i][j] += m[i][k] * other.m[k][j];
            }
        }
    }
    return result;
}

Vector3 Matrix4::operator*(const Vector3& vector) const {
    float x = m[0][0] * vector.x + m[0][1] * vector.y + m[0][2] * vector.z + m[0][3];
    float y = m[1][0] * vector.x + m[1][1] * vector.y + m[1][2] * vector.z + m[1][3];
    float z = m[2][0] * vector.x + m[2][1] * vector.y + m[2][2] * vector.z + m[2][3];
    float w = m[3][0] * vector.x + m[3][1] * vector.y + m[3][2] * vector.z + m[3][3];
    
    if (w != 0) {
        return Vector3(x / w, y / w, z / w);
    }
    return Vector3(x, y, z);
}

Vector3 Matrix4::transformVector(const Vector3& vector) const {
    float x = m[0][0] * vector.x + m[0][1] * vector.y + m[0][2] * vector.z;
    float y = m[1][0] * vector.x + m[1][1] * vector.y + m[1][2] * vector.z;
    float z = m[2][0] * vector.x + m[2][1] * vector.y + m[2][2] * vector.z;
    return Vector3(x, y, z);
}

Matrix4& Matrix4::operator*=(const Matrix4& other) {
    *this = *this * other;
    return *this;
}

Matrix4 Matrix4::identity() {
    Matrix4 result;
    return result;
}

Matrix4 Matrix4::translation(const Vector3& translation) {
    Matrix4 result;
    result.m[0][3] = translation.x;
    result.m[1][3] = translation.y;
    result.m[2][3] = translation.z;
    return result;
}

Matrix4 Matrix4::rotationX(float angle) {
    Matrix4 result;
    float c = std::cos(angle);
    float s = std::sin(angle);
    result.m[1][1] = c;
    result.m[1][2] = -s;
    result.m[2][1] = s;
    result.m[2][2] = c;
    return result;
}

Matrix4 Matrix4::rotationY(float angle) {
    Matrix4 result;
    float c = std::cos(angle);
    float s = std::sin(angle);
    result.m[0][0] = c;
    result.m[0][2] = s;
    result.m[2][0] = -s;
    result.m[2][2] = c;
    return result;
}

Matrix4 Matrix4::rotationZ(float angle) {
    Matrix4 result;
    float c = std::cos(angle);
    float s = std::sin(angle);
    result.m[0][0] = c;
    result.m[0][1] = -s;
    result.m[1][0] = s;
    result.m[1][1] = c;
    return result;
}

Matrix4 Matrix4::scale(const Vector3& scale) {
    Matrix4 result;
    result.m[0][0] = scale.x;
    result.m[1][1] = scale.y;
    result.m[2][2] = scale.z;
    return result;
}

Matrix4 Matrix4::lookAt(const Vector3& position, const Vector3& target, const Vector3& up) {
    Vector3 cZ = (target - position).normalized();
    Vector3 cX = up.cross(cZ).normalized();
    Vector3 cY = cZ.cross(cX).normalized();
    
    Matrix4 result;
    result.m[0][0] = cX.x; result.m[0][1] = cX.y; result.m[0][2] = cX.z; result.m[0][3] = -cX.dot(position);
    result.m[1][0] = cY.x; result.m[1][1] = cY.y; result.m[1][2] = cY.z; result.m[1][3] = -cY.dot(position);
    result.m[2][0] = cZ.x; result.m[2][1] = cZ.y; result.m[2][2] = cZ.z; result.m[2][3] = -cZ.dot(position);
    result.m[3][0] = 0;    result.m[3][1] = 0;    result.m[3][2] = 0;    result.m[3][3] = 1;
    
    return result;
}

Matrix4 Matrix4::transpose() const {
    Matrix4 result;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result.m[i][j] = m[j][i];
        }
    }
    return result;
}

void Matrix4::setIdentity() {
    std::memset(m, 0, sizeof(m));
    m[0][0] = m[1][1] = m[2][2] = m[3][3] = 1.0f;
}

void Matrix4::set(int row, int col, float value) {
    m[row][col] = value;
}

float Matrix4::get(int row, int col) const {
    return m[row][col];
}

// Simplified inverse for view matrices (orthonormal)
Matrix4 Matrix4::inverse() const {
    Matrix4 result;
    
    // For orthonormal matrices (like camera matrices), inverse = transpose of rotation part
    // and negate translation part
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            result.m[i][j] = m[j][i];
        }
    }
    
    result.m[0][3] = -(m[0][3] * result.m[0][0] + m[1][3] * result.m[0][1] + m[2][3] * result.m[0][2]);
    result.m[1][3] = -(m[0][3] * result.m[1][0] + m[1][3] * result.m[1][1] + m[2][3] * result.m[1][2]);
    result.m[2][3] = -(m[0][3] * result.m[2][0] + m[1][3] * result.m[2][1] + m[2][3] * result.m[2][2]);
    
    return result;
}
