#include <neo/Terminal.h>
#include <cstdio>
#include <iostream>
#include <string>

#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>
#include <conio.h>
#endif

namespace Neo
{
#define ENSURE_INITIALIZED() if(!m_Initialized) setup();

    void Questions::Add(int32 index, const std::string &text, UserInputDataType type)
    {
        m_Questions.emplace(m_Questions.begin() + index, text, type);
    }

    void Questions::Add(int32 index, const std::string &text, const NumberRange& range)
    {
        m_Questions.emplace(m_Questions.begin() + index, text, range);
    }

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
        ENSURE_INITIALIZED();
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

    void Terminal::Clear()
    {
#if defined(WIN32)
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD coordScreen = {0, 0};
        DWORD cCharsWritten;
        CONSOLE_SCREEN_BUFFER_INFO csbi;

        if(!GetConsoleScreenBufferInfo(hConsole, &csbi))
            return;

        DWORD dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

        if(!FillConsoleOutputCharacter(hConsole, (WCHAR)' ', dwConSize, coordScreen, &cCharsWritten))
            return;
        if(!GetConsoleScreenBufferInfo(hConsole, &csbi))
            return;
        if(!FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten))
            return;

        SetConsoleCursorPosition(hConsole, coordScreen);
#endif
#ifdef defined(unix) || defined(__APPLE__)
        printf("\x1B[2J\x1B[H");
#endif
    }

    void Terminal::Pause()
    {
        PushStyle(TerminalStyle{Color::Green, Color::Black});
        Print("(~) Press any key to continue");
        PopStyle();
#ifdef WIN32
        _getch();
#endif
    }

    void Terminal::Ask(Questions& questions)
    {
        for (Questions::Question& question : questions.m_Questions)
        {
            Questions::Answer& answer = question.Answer;

            std::string additionalInfo;
            if (question.Type == UserInputDataType::Boolean)
            {
                additionalInfo = " (y/n) (default: y)";
            }

            PushStyle(TerminalStyle{Color::Green, Color::Black});
            Print("(?) {}{}", question.Text, additionalInfo);
            PopStyle();

            switch (question.Type)
            {
                case UserInputDataType::String:
                {
                    std::string s;
                    std::getline(std::cin, s);

                    //Oh man i dont really like that implementation...
                    answer.Value.Text = new char[s.size() + 1];
                    answer.Value.Text[s.size()] = '\0';
                    memcpy(answer.Value.Text, s.data(), s.size());
                    break;
                }
                case UserInputDataType::Int32:
                {
                    Questions::NumberRange& range = question.NumberRange;
                    while (true)
                    {
                        std::cin >> answer.Value.NumberValue;

                        if (std::cin.fail()) {
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                            PushStyle(TerminalStyle{Color::Red, Color::Black});
                            Print("Value is not a number! Please enter value again.");
                            PopStyle();
                        }
                        else if (answer.Value.NumberValue > range.Maximal)
                        {
                            PushStyle(TerminalStyle{Color::Red, Color::Black});
                            Print("Value is too big! Please enter value again.");
                            PopStyle();
                        } else if (answer.Value.NumberValue < range.Minimal)
                        {
                            PushStyle(TerminalStyle{Color::Red, Color::Black});
                            Print("Value is too small! Please enter value again.");
                            PopStyle();
                        }
                        else if (range.RequireEven && answer.Value.NumberValue % 2 != 0)
                        {
                            PushStyle(TerminalStyle{Color::Red, Color::Black});
                            Print("Value is not even! Please enter value again.");
                            PopStyle();
                        }
                        else {
                            break;
                        }
                    }
                    break;
                }
                case UserInputDataType::Boolean:
                {
                    std::string s;
                    std::cin >> s;

                    answer.Value.BoolValue = s != "n";
                    break;
                }
            }
        }
    }

    const Questions::Answer& Questions::GetAnswer(int32 index) const
    {
        return m_Questions[index].Answer;
    }

    int32 Terminal::Getch()
    {
        return _getch();
    }

    uint32 Terminal::Menu(const std::vector<std::string> &options)
    {
        int32 choose = 0;

        auto draw = [&]()
        {
            Clear();

            for (int32 i = 0; i < options.size();)
            {
                const std::string& option = options[i];

                Color c = i == choose ? Color::Green : Color::White;

                PushStyle(TerminalStyle{c, Color::Black});
                Print("{}. {}", ++i, option);
                PopStyle();
            }
        };

        draw();

        while (true)
        {
#ifdef WIN32
            int32 key = static_cast<int32>(_getch());
#endif
            switch (key)
            {
                case 13:
                    return choose;
                case 80:
                    if (choose == options.size() - 1)
                        break;
                    choose++;
                    break;
                case 72:
                    if (choose == 0)
                        break;
                    choose--;
                    break;

                default:
                    break;
            }

            draw();
        }

    }
}