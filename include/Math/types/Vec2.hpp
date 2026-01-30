#pragma once
#include <cmath>

namespace Math
{
    struct Vec2
    {
        float x;
        float y;

        Vec2() : x(0), y(0) {}
        Vec2(float x, float y) : x(x), y(y) {}

        float distance(const Vec2 &other)
        {
            return sqrt(pow((other.x - this->x), 2) + pow((other.y - this->y), 2));
        }
        Vec2 betweenPoint(const Vec2 &other)
        {
            return {(this->x + other.x) / 2, (this->y + other.y) / 2};
        }

        float angle(const Vec2 &other)
        {
            float dx = other.x - this->x;
            float dy = other.y - this->y;
            float anguloRad = atan2(dy, dx);
            return anguloRad;
        }

        Vec2 operator+(const Vec2 &other) const { return {this->x + other.x, this->y + other.y}; }
        Vec2 operator-(const Vec2 &other) const { return {this->x - other.x, this->y - other.y}; }
        Vec2 operator*(float scalar)      const { return {this->x * scalar, this->y * scalar}; }
    };

}