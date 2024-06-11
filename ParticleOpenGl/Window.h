#pragma once
#include "IWindow.h"
#include <memory>
#include "UIContext.h"
#include "OpenGlContext.h"
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "PropertyPanel.h"
#include "SceneView.h"
#include "FileBrowser.h"
#include "ItemsSelectionPanel.h"
#include "AddingPanel.h"
#include "ControlPanel.h"


class Window : public IWindow
{
public:
    Window() : IsRunning(true), window(nullptr), application(nullptr)
    {
        UICtx = std::make_unique<UIContext>();
        RenderCtx = std::make_unique<OpenGlContext>();
        application = std::make_shared<Application>();
    }

    ~Window();

    bool Init(int width, int height, const std::string& title);

    void Render();

    void* get_native_window() { return window; };

    void set_native_window(void* window)
    {
        this->window = (GLFWwindow*)window;
    }

    void on_resize(int width, int height);

    void on_close();

    bool is_running() { return IsRunning; }

private:

    GLFWwindow* window;
    std::shared_ptr<Application> application;

    // Render contexts
    std::unique_ptr<UIContext> UICtx;

    std::unique_ptr<OpenGlContext> RenderCtx;

    std::unique_ptr<PropertyPanel> propertyPanel;

    std::unique_ptr<ItemsSelectionPanel> itemsSelectionPanel;

    std::unique_ptr<SceneView> sceneView;

    std::unique_ptr<FileBrowser> fileBrowser;

    std::unique_ptr<AddingPanel> addingPanel;

    std::unique_ptr<ControlPanel> controlPanel;

    bool IsRunning;
    
};

