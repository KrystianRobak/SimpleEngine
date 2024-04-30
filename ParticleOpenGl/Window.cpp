#include "Window.h"

bool Window::Init(int width, int height, const std::string& title)
{
    this->width = width;
    this->height = height;
    this->title = title;

    mRenderCtx->init(this);

    mUICtx->init(this);
    propertyPanel = std::make_unique<PropertyPanel>();
    sceneView = std::make_unique<SceneView>();
    fileBrowser = std::make_unique<FileBrowser>();
   
    return mIsRunning;
}

Window::~Window()
{
    mUICtx->end();

    mRenderCtx->end();
}

void Window::on_resize(int width, int height)
{
    this->width = width;
    this->height = height;

    sceneView->resize(this->width, this->height);
    Render();
}

void Window::on_close()
{
    mIsRunning = false;
}

void Window::Render()
{
    // Clear the view
    mRenderCtx->pre_render();

    // Initialize UI components
    mUICtx->pre_render();

    // render scene to framebuffer and add it to scene view

    sceneView->Render();

    propertyPanel->Render(sceneView.get());

    fileBrowser->Render();

    // Render the UI 
    mUICtx->post_render();

    // Render end, swap buffers
    mRenderCtx->post_render();

}