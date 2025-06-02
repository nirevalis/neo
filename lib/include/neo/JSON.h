#pragma once

#include <neo/Primitives.h>
#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>

namespace Neo
{
    enum class JSONOpenMode : uint8
    {
        Read = (1 << 0),
        Write = (1 << 1),
    };

    ENABLE_BITMASK_OPERATORS(JSONOpenMode);

    class JSON
    {
    private:
        nlohmann::json m_Data;
        JSONOpenMode m_OpenMode;
        std::fstream m_Stream;

    public:
        JSON() = default;
        ~JSON() = default;

        [[nodiscard]] nlohmann::json& Open(const std::filesystem::path& path, JSONOpenMode mode = JSONOpenMode::Read);
        void Flush();
        void Close();
    };
}