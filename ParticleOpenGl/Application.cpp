#include "Application.h"

Application::Application(const std::string& app_name)
{
    window = std::make_unique<Window>();
    window->init(1024, 720, app_name);

}

void Application::loop()
{
    while (window->is_running())
    {
        window->Render();
    }
}