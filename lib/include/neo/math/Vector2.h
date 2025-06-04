#pragma once

namespace Neo
{
    struct Vector2
    {
        union
        {
            struct
            {
                float X, Y;
            };

            float Raw[2];
        };

        constexpr Vector2() : X(0), Y(0)
        {

        }

        constexpr Vector2(const float x, const float y) : X(x), Y(y)
        {

        }

        const static Vector2 Zero;
        const static Vector2 One;

        float* GetValuePointer()
        {
            return Raw;
        }

        constexpr bool operator==(const Vector2& right) const
        {
            return X == right.X && Y == right.Y;
        }

        constexpr Vector2 operator+(const Vector2& right) const
        {
            return Vector2(X + right.X, Y + right.Y);
        }

        constexpr Vector2 operator-(const Vector2& right) const
        {
            return Vector2(X - right.X, Y - right.Y);
        }

        constexpr bool operator<(const Vector2& right) const
        {
            return X < right.X && Y < right.Y;
        }

        constexpr bool operator>(const Vector2& right) const
        {
            return X > right.X && Y > right.Y;
        }

        constexpr bool operator<=(const Vector2& right) const
        {
            return X < right.X && Y < right.Y;
        }

        constexpr bool operator>=(const Vector2& right) const
        {
            return X >= right.X && Y >= right.Y;
        }

        constexpr Vector2 operator*(const Vector2& right) const
        {
            return Vector2(X * right.X, Y * right.Y);
        }

        constexpr Vector2 operator*(float value) const
        {
            return Vector2(X * value, Y * value);
        }

        constexpr Vector2 operator/(float value) const
        {
            return Vector2(X / value, Y / value);
        }
    };
}