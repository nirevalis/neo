#pragma once

#include <neo/Primitives.h>
#include <span>

#define BOOTSTRAP_AND_RETURN(app,argc,argv) Neo::Bootstrap(app,argc,argv); return app.GetExitCode();

namespace Neo
{
    enum class ApplicationStatus : uint8
    {
        Success = 0,
        Error = 1
    };

    class IApplication
    {
    private:
        static IApplication* m_Instance;
        ApplicationStatus m_Status;

    public:
        IApplication();
        virtual ~IApplication() = default;

        template <typename T>
        static T& Get()
        {
            return *reinterpret_cast<T*>(m_Instance);
        };

        [[nodiscard]] int32 GetExitCode() const;
        void SetStatus(ApplicationStatus status);

        virtual void Run(const std::span<const char*> &args) = 0;
    };

    constexpr static void Bootstrap(IApplication& app, const int32 argc, const char** argv)
    {
        app.Run(std::span(argv, argc));
    }
}