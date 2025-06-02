#pragma once

#include <span>

#define BOOTSTRAP_AND_RETURN(app,argc,argv) Neo::Bootstrap(app,argc,argv); return app.GetExitCode();

namespace Neo
{
    class IApplication
    {
    public:
        IApplication() = default;
        virtual ~IApplication() = default;

        int GetExitCode()
        {
            return 21;
        }

        virtual void Run(const std::span<const char*> &args) = 0;
    };

    constexpr static void Bootstrap(IApplication& app, const int argc, const char** argv)
    {
        app.Run(std::span(argv, argc));
    }
}