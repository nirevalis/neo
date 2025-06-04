#pragma once

#include "Vector2.h"
#include "Math.h"

namespace Neo
{
    struct Vector3
    {
        union
        {
            struct
            {
                float X, Y, Z;
            };

            float Raw[3];
        };

        constexpr Vector3() : X(0), Y(0), Z(0)
        {

        }

        constexpr Vector3(float x, float y, float z) : X(x), Y(y), Z(z)
        {

        }

        constexpr Vector3(const Vector2& xy, float z) : X(xy.X), Y(xy.Y), Z(z)
        {

        }

        const static Vector3 Zero;
        const static Vector3 One;

        float* GetValuePointer()
        {
            return Raw;
        }

        constexpr static Vector3 Cross(const Vector3& source, const Vector3& other)
        {
            return Vector3(
                source.Y * other.Z - source.Z * other.Y,
                source.Z * other.X - source.X * other.Z,
                source.X * other.Y - source.Y * other.X
            );
        }

        constexpr static float Dot(const Vector3& left, const Vector3& right)
        {
            return left.X * right.X + left.Y * right.Y + left.Z * right.Z;
        }

        constexpr static Vector3 Normalize(const Vector3& source)
        {
            Vector3 v = source;

            float length = Math::Sqrt(source.X * source.X + source.Y * source.Y + source.Z * source.Z);
            if (length >= Math::Epsilon)
            {
                float inv = 1.0f / length;
                v.X *= inv;
                v.Y *= inv;
                v.Z *= inv;
            }

            return v;
        }

        constexpr Vector3 operator+(const Vector3& right) const
        {
            return Vector3(X + right.X, Y + right.Y, Z + right.Z);
        }

        constexpr Vector3 operator-(const Vector3& right) const
        {
            return Vector3(X - right.X, Y - right.Y, Z - right.Z);
        }

        constexpr Vector3 operator-() const
        {
            return Vector3(-X, -Y, -Z);
        }

        constexpr Vector3 operator+=(const Vector3& right)
        {
            this->X += right.X;
            this->Y += right.Y;
            this->Z += right.Z;
            return *this;
        }

        constexpr Vector3 operator-=(const Vector3& right)
        {
            this->X -= right.X;
            this->Y -= right.Y;
            this->Z -= right.Z;
            return *this;
        }

        constexpr Vector3 operator*(const Vector3& right) const
        {
            return Vector3(X * right.X, Y * right.Y, Z * right.Z);
        }

        constexpr Vector3 operator*(float value) const
        {
            return Vector3(X * value, Y * value, Z * value);
        }

        constexpr Vector3 operator/(float value) const
        {
            return Vector3(X / value, Y / value, Z / value);
        }
    };
}