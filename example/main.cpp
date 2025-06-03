#include <iostream>
#include <neo/JSON.h>
#include <neo/IApplication.h>

using namespace Neo;
class ExampleApplication : public IApplication
{
public:
    void Run(const std::span<const char *> &args) override
    {
        SetStatus(ApplicationStatus::Error);
        JSON json;

        nlohmann::json& obj = json.Open("test.json", JSONOpenMode::Write);
        obj["testy"] = "wsyzsyo dzila";
        json.Close();
    }
};

int32 main(const int32 argc, const char** argv)
{
    ExampleApplication app;
    BOOTSTRAP_AND_RETURN(app, argc, argv);
}