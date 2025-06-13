#include <neo/JSON.h>
#include <neo/Terminal.h>

namespace Neo
{
    nlohmann::json &JSON::Open(const std::filesystem::path &path, JSONOpenMode mode, uint8 indentation)
    {
        m_OpenMode = mode;
        m_Indentation = indentation;
        m_FilePath = path;

        if (HasFlag(mode, JSONOpenMode::Read))
        {
            std::ifstream inFile(path);
            if (!inFile)
                Terminal::Print("Failed to open JSON file for reading: {}", path.string());

            inFile >> m_Data;
        }

        return m_Data;
    }

    void JSON::Flush()
    {
        if (!HasFlag(m_OpenMode, JSONOpenMode::Write))
            return;

        std::ofstream outFile(m_FilePath);
        if (!outFile)
            Terminal::Print("Failed to open JSON file for writing: {}", m_FilePath.string());

        outFile << m_Data.dump(m_Indentation);
    }

    void JSON::Close()
    {
        if (HasFlag(m_OpenMode, JSONOpenMode::Write))
        {
            Flush();
        }
        m_OpenMode = JSONOpenMode::None;
        m_Data.clear();
    }
}
