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


class Window : public IWindow
{
public:
    Window() : mIsRunning(true), window(nullptr)
    {
        mUICtx = std::make_unique<UIContext>();
        mRenderCtx = std::make_unique<OpenGlContext>();
        
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

    bool is_running() { return mIsRunning; }

private:

    GLFWwindow* window;

    // Render contexts
    std::unique_ptr<UIContext> mUICtx;

    std::unique_ptr<OpenGlContext> mRenderCtx;

    std::unique_ptr<PropertyPanel> propertyPanel;

    std::unique_ptr<ItemsSelectionPanel> itemsSelectionPanel;

    std::unique_ptr<SceneView> sceneView;

    std::unique_ptr<FileBrowser> fileBrowser;

    bool mIsRunning;
    
};

