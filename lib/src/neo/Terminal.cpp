#include <neo/Terminal.h>
#include <cstdio>

#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>
#endif

namespace Neo
{
#define ENSURE_INITIALIZED() if(!m_Initialized) setup();
    void Terminal::setup()
    {
        m_StyleStack.emplace(Color::White, Color::Black);
#ifdef WIN32
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        DWORD dwMode = 0;
        GetConsoleMode(hOut, &dwMode);
        dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        SetConsoleMode(hOut, dwMode);
#endif
        m_Initialized = true;
    }

    void Terminal::applyStyle(TerminalStyle &style)
    {
        printf("\x1b[38;2;%i;%i;%im", style.Foreground.R, style.Foreground.G, style.Foreground.B);
        printf("\x1b[48;2;%i;%i;%im", style.Background.R, style.Background.G, style.Background.B);
    }

    void Terminal::PushStyle(const TerminalStyle& style)
    {
        m_StyleStack.emplace(style.Foreground, style.Background);
    }

    void Terminal::PopStyle(uint8 count)
    {
        for (uint8 i = 0; i < count; i++)
            m_StyleStack.pop();
    }

    void Terminal::printStringColored(const std::string_view& str, const std::string& end)
    {
        ENSURE_INITIALIZED();

        applyStyle(m_StyleStack.top());
        printf("%s%s\x1b[0m", str.data(), end.data());
    }
}