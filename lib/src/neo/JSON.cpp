#include <neo/JSON.h>

namespace Neo
{
    nlohmann::json &JSON::Open(const std::filesystem::path &path, JSONOpenMode mode, uint8 indentation)
    {
        m_OpenMode = mode;
        m_Indentation = indentation;

        if (HasFlag(mode, JSONOpenMode::Read))
        {
            m_Stream.open(path.string(),  std::ios::in);
            m_Stream >> m_Data;
            m_Stream.close();
        }

        if (HasFlag(mode, JSONOpenMode::Write))
            m_Stream.open(path.string(),  std::ios::out);

        return m_Data;
    }

    void JSON::Flush()
    {
        m_Stream.clear();
        m_Stream.seekp(0, std::ios::beg);
        m_Stream << m_Data.dump(m_Indentation);
    }

    void JSON::Close()
    {
        if (m_Stream.is_open())
        {
            Flush();
            m_Stream.close();
        }
    }

}