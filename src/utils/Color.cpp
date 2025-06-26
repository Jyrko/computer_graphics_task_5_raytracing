#include "Color.hpp"
#include <algorithm>

Color::Color() : r(0), g(0), b(0) {}

Color::Color(float r, float g, float b) : r(r), g(g), b(b) {}

Color::Color(const Color& other) : r(other.r), g(other.g), b(other.b) {}

Color Color::operator+(const Color& other) const {
    return Color(r + other.r, g + other.g, b + other.b);
}

Color Color::operator*(float scalar) const {
    return Color(r * scalar, g * scalar, b * scalar);
}

Color Color::operator*(const Color& other) const {
    return Color(r * other.r, g * other.g, b * other.b);
}

Color& Color::operator+=(const Color& other) {
    r += other.r;
    g += other.g;
    b += other.b;
    return *this;
}

Color& Color::operator*=(float scalar) {
    r *= scalar;
    g *= scalar;
    b *= scalar;
    return *this;
}

Color Color::clamp() const {
    return Color(
        std::max(0.0f, std::min(1.0f, r)),
        std::max(0.0f, std::min(1.0f, g)),
        std::max(0.0f, std::min(1.0f, b))
    );
}

uint32_t Color::toRGB() const {
    Color clamped = clamp();
    uint8_t red = static_cast<uint8_t>(clamped.r * 255);
    uint8_t green = static_cast<uint8_t>(clamped.g * 255);
    uint8_t blue = static_cast<uint8_t>(clamped.b * 255);
    return (red << 16) | (green << 8) | blue;
}

Color Color::black() {
    return Color(0, 0, 0);
}

Color Color::white() {
    return Color(1, 1, 1);
}

Color Color::red() {
    return Color(1, 0, 0);
}

Color Color::green() {
    return Color(0, 1, 0);
}

Color Color::blue() {
    return Color(0, 0, 1);
}

Color operator*(float scalar, const Color& color) {
    return color * scalar;
}
