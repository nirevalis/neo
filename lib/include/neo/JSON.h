#pragma once

#include <neo/Primitives.h>
#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>

namespace Neo
{
    enum class JSONOpenMode : uint8
    {
        None  = 0,
        Read = (1 << 0),
        Write = (1 << 1),
    };

    ENABLE_BITMASK_OPERATORS(JSONOpenMode);

    class JSON
    {
    private:
        std::filesystem::path m_FilePath;
        uint8 m_Indentation;
        nlohmann::json m_Data;
        JSONOpenMode m_OpenMode;
        std::fstream m_Stream;

    public:
        JSON() = default;
        ~JSON() = default;

        JSON(const JSON&) = delete;

        [[nodiscard]] nlohmann::json& Open(const std::filesystem::path& path, JSONOpenMode mode = JSONOpenMode::Read, uint8 indentation = 0);
        void Flush();
        void Close();
    };
}