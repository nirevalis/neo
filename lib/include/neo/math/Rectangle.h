#pragma once

#include "Vector2.h"

namespace Neo
{
    struct Rectangle
    {
    private:
        void ResetConsts()
        {
            Center = Vector2(X, Y) + Vector2(Width, Height) * 0.5f;
        }
    public:
        const static Rectangle Zero;

        float X;
        float Y;
        float Width;
        float Height;

        Vector2 Center;

        Rectangle() : X(0), Y(0), Width(0), Height(0)
        {
            ResetConsts();
        };

        Rectangle(float x, float y, float width, float height) : X(x), Y(y), Width(width), Height(height)
        {
            ResetConsts();
        };

        Rectangle(const Vector2& position, const Vector2& size) : X(position.X), Y(position.Y), Width(size.X), Height(size.Y)
        {
            ResetConsts();
        };
    };
}