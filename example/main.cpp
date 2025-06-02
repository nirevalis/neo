#include <iostream>
#include <neo/JSON.h>
#include <neo/IApplication.h>

class ExampleApplication : public Neo::IApplication
{
public:
    void Run(const std::span<const char *> &args) override
    {
        
    }
};

int main(const int argc, const char** argv)
{
    ExampleApplication app;
    BOOTSTRAP_AND_RETURN(app, argc, argv);
}