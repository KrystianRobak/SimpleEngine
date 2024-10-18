#include "Window.h"

bool Window::Init(int width, int height, const std::string& title)
{
    this->width = width;
    this->height = height;
    this->title = title;

    RenderCtx->init(this);

    UICtx->init(this);
   
    return IsRunning;
}

Window::~Window()
{
    UICtx->end();

    RenderCtx->end();
}

void Window::on_resize(int width, int height)
{
    this->width = width;
    this->height = height;

    //sceneView->resize(this->width, this->height);
}

void Window::on_close()
{
    IsRunning = false;
}

void Window::PreRender()
{

    RenderCtx->pre_render();

    UICtx->pre_render();

}

void Window::PostRender()
{

    UICtx->post_render();

    RenderCtx->post_render();
}