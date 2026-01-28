#pragma once

namespace KMath
{
    struct Vector2
    {
        static Vector2 One;
        static Vector2 Zero;

        float x;
        float y;

        Vector2() : x(0.f), y(0.f) {}
        Vector2(float inX, float inY) : x(inX), y(inY) {}
    };
}