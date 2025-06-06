#pragma once

#include <neo/Primitives.h>
#include <neo/math/Color.h>
#include <string_view>
#include <format>
#include <utility>
#include <vector>
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

    enum class UserInputDataType : uint8
    {
        String,
        Int32,
        Boolean
    };

    class Questions
    {
    public:
        struct NumberRange
        {
            int32 Minimal;
            int32 Maximal;
            bool RequireEven;

            NumberRange(int32 min, int32 max, bool requireEven) : Minimal(min), Maximal(max), RequireEven(requireEven) {}
        };

    private:
        friend class Terminal;

        struct Answer
        {
            UserInputDataType Type;

            union ValueUnion
            {
                char* Text;
                struct { int32 NumberValue; int32 _i32fill; };
                struct { bool BoolValue; uint8 _i8fill[7]; };

                ValueUnion() : Text(nullptr) {}
                ~ValueUnion() {}
            } Value;

            explicit Answer(UserInputDataType type) : Type(type)
            {
                if (Type == UserInputDataType::String)
                    Value.Text = nullptr;
            }

            ~Answer()
            {
                if (Type == UserInputDataType::String && Value.Text)
                    delete[] Value.Text;
            }

            Answer(const Answer&) = delete;
            Answer& operator=(const Answer&) = delete;

            Answer(Answer&& other) noexcept : Type(other.Type), Value{}
            {
                if (Type == UserInputDataType::String)
                {
                    Value.Text = other.Value.Text;
                    other.Value.Text = nullptr;
                }
                else if (Type == UserInputDataType::Int32)
                {
                    Value.NumberValue = other.Value.NumberValue;
                }
                else if (Type == UserInputDataType::Boolean)
                {
                    Value.BoolValue = other.Value.BoolValue;
                }
            }

            Answer& operator=(Answer&& other) noexcept
            {
                if (this != &other)
                {
                    if (Type == UserInputDataType::String && Value.Text)
                        delete[] Value.Text;

                    Type = other.Type;

                    if (Type == UserInputDataType::String)
                    {
                        Value.Text = other.Value.Text;
                        other.Value.Text = nullptr;
                    }
                    else if (Type == UserInputDataType::Int32)
                    {
                        Value.NumberValue = other.Value.NumberValue;
                    }
                    else if (Type == UserInputDataType::Boolean)
                    {
                        Value.BoolValue = other.Value.BoolValue;
                    }
                }
                return *this;
            }
        };

        struct Question
        {
            std::string Text;
            UserInputDataType Type;
            NumberRange NumberRange;
            Answer Answer;

            Question(std::string text, UserInputDataType type) : Text(std::move(text)), Type(type), NumberRange(INT32_MIN, INT32_MAX, false), Answer(type) {}
            Question(std::string text, const struct NumberRange& range) : Text(std::move(text)), Type(UserInputDataType::Int32), NumberRange(range), Answer(UserInputDataType::Int32) {}
        };

        std::vector<Question> m_Questions;
    public:
        void Add(int32 index, const std::string& text, UserInputDataType type = UserInputDataType::String);
        void Add(int32 index, const std::string& text, const NumberRange& range);
        [[nodiscard]] const Answer& GetAnswer(int32 index) const;
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

        static void Pause();
        static void Clear();

        static void Ask(Questions& questions);
        static uint32 Menu(const std::vector<std::string>& options);
        static int32 Getch();

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