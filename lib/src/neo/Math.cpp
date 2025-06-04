#include <neo/math/Math.h>

#include <neo/math/Vector2.h>
#include <neo/math/Vector3.h>
#include <neo/math/Rectangle.h>
#include <neo/math/Color.h>

namespace Neo
{
    const Vector2 Vector2::One = Vector2(1, 1);
    const Vector2 Vector2::Zero = Vector2(0, 0);

    const Vector3 Vector3::One = Vector3(1, 1, 1);
    const Vector3 Vector3::Zero = Vector3(0, 0, 0);

    const Rectangle Rectangle::Zero = Rectangle(0, 0, 0, 0);

    const Color Color::Red = Color(255,0,0);
    const Color Color::Green = Color(0,255,0);
    const Color Color::Blue = Color(0,0,255);
    const Color Color::Black = Color(0,0,0);
    const Color Color::White = Color(255,255,255);
    const Color Color::Yellow = Color(255,255,0);
    const Color Color::Cyan = Color(0,255,255);
    const Color Color::Magenta = Color(255,0,255);
    const Color Color::Gray = Color(128,128,128);
    const Color Color::Orange = Color(255,165,0);
    const Color Color::Purple = Color(128,0,128);
    const Color Color::Brown = Color(165,42,42);

    const std::array<Color, 12> Color::Colors = {
        Color::Red, Color::Green, Color::Blue, Color::Black, Color::White,
           Color::Yellow, Color::Cyan, Color::Magenta, Color::Gray, Color::Orange,
           Color::Purple, Color::Brown
    };
}