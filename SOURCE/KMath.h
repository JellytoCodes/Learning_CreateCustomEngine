#pragma once
#include "CommonInclude.h"

namespace KMath
{
#define PI 3.141592f

    static float ConvertToDegree(float radian) { return radian * (180 / PI); }

    struct Vector2
    {

    	static float Dot(Vector2& lhs, Vector2& rhs)
	    {
		    return (lhs.x * rhs.x) + (lhs.y * rhs.y);
	    }
	    
	    static float Cross(Vector2& lhs, Vector2& rhs)
	    {
		    return (lhs.x * rhs.y) - (lhs.y * rhs.x);
	    }

        static Vector2 One;
        static Vector2 Zero;
        static Vector2 Right;
        static Vector2 Left;
        static Vector2 Up;
        static Vector2 Down;

        float x;
        float y;

        Vector2() : x(0.f), y(0.f) {}
        Vector2(float inX, float inY) : x(inX), y(inY) {}

    	Vector2 operator+(Vector2 other)
        {
	        return Vector2(x + other.x, y + other.y);
        }

    	Vector2 operator-()
        {
	        return Vector2(-x, -y);
        }

        Vector2 operator-(Vector2 other)
        {
	        return Vector2(x - other.x, y - other.y);
        }

        Vector2 operator*(Vector2 other)
        {
	        return Vector2(x * other.x, y * other.y);
        }

    	void operator+=(Vector2 other)
        {
	        x+= other.x;
            y+= other.y;
        }

    	Vector2 operator*(float value)
        {
	        return Vector2(x * value, y * value);
        }

		Vector2 operator/(float value)
        {
	        return Vector2(x / value, y / value);
        }

        bool operator==(Vector2 other)
        {
	        return (x == other.x) && (y == other.y); 
        }


        void Clear()
        {
	        x = 0.f;
            y = 0.f;
        }

        float Length()
        {
	        return sqrtf((x * x) + (y * y));
        }

        Vector2 Normalize()
        {
	        float len = Length();
            x /= len;
            y /= len;

            return *this;
        }

        Vector2 Rotate(float degree)
		{
			float radian = (degree / 180.f) * PI;
			this->Normalize();
			float inX = cosf(radian) * x - sinf(radian) * y;
			float inY = sinf(radian) * x + cosf(radian) * y;

			return Vector2(inX, inY);
		}
    };
}
