#pragma once

#include <neo/Primitives.h>
#include <neo/math/Color.h>
#include <string_view>
#include <format>
#include <stack>

namespace Neo
{
    struct TerminalStyle
    {
        Color Foreground;
        Color Background;

        TerminalStyle() = default;

        TerminalStyle(const Color& foreground, const Color& background) : Foreground(foreground), Background(background) {}
    };


    class Terminal
    {
    private:
        inline static bool m_Initialized = false;
        inline static std::stack<TerminalStyle> m_StyleStack;
        static void applyStyle(TerminalStyle& style);
        static void setup();
        static void printStringColored(const std::string_view& str, const std::string& end = "\n");

    public:
        Terminal() = delete;
        ~Terminal() = delete;

        static void PushStyle(const TerminalStyle& style);
        static void PopStyle(uint8 count = 1);

        template <typename... Args>
        inline static void Print(std::format_string<Args...> format, Args&&... args)
        {
            printStringColored( std::format(format, std::forward<Args>(args)...));
        }

        template <typename... Args>
        inline static void PrintNoNewLine(std::format_string<Args...> format, Args&&... args)
        {
            printStringColored( std::format(format, std::forward<Args>(args)...), "");
        }
    };
}