#pragma once

#include <neo/Primitives.h>
#include <array>

namespace Neo
{
    struct Color
    {
        union
        {
            struct
            {
                uint8 R, G, B;
            };

            uint8 Raw[3];
        };

        constexpr Color() : R(0), G(0), B(0)
        {

        }

        constexpr Color(uint8 r, uint8 g, uint8 b) : R(r), G(g), B(b)
        {

        }

        const static Color Red;
        const static Color Green;
        const static Color Blue;
        const static Color White;
        const static Color Black;
        const static Color Yellow;
        const static Color Cyan;
        const static Color Magenta;
        const static Color Gray;
        const static Color Orange;
        const static Color Purple;
        const static Color Brown;
        const static std::array<Color, 12> Colors;
    };
}