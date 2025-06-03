#include <neo/IApplication.h>

namespace Neo
{
    IApplication* IApplication::m_Instance = nullptr;

    IApplication::IApplication()
    {
        m_Instance = this;
    }

    int32 IApplication::GetExitCode() const
    {
        return static_cast<int32>(m_Status);
    }

    void IApplication::SetStatus(ApplicationStatus status)
    {
        m_Status = status;
    }

}