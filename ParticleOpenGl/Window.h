#pragma once
#include "IWindow.h"
#include <memory>
#include "UIContext.h"
#include "OpenGlContext.h"
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>


class Window : public IWindow
{
public:
    Window() : IsRunning(true), window(nullptr)
    {
        UICtx = std::make_unique<UIContext>();
        RenderCtx = std::make_unique<OpenGlContext>();
    }

    ~Window();

    bool Init(int width, int height, const std::string& title);

    void* get_native_window() { return window; };

    void set_native_window(void* window)
    {
        this->window = (GLFWwindow*)window;
    }

    void on_resize(int width, int height);

    void on_close();

    void PreRender();

    void PostRender();

    bool is_running() { return IsRunning; }

private:

    GLFWwindow* window;

    // Render contexts
    std::unique_ptr<UIContext> UICtx;

    std::unique_ptr<OpenGlContext> RenderCtx;

    bool IsRunning;
    
};

