#include "OpenGlContext.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdio>

static void on_window_size_callback(GLFWwindow* window, int width, int height)
{
    auto pWindow = static_cast<IWindow*>(glfwGetWindowUserPointer(window));
    pWindow->on_resize(width, height);
}

bool OpenGlContext::init(IWindow* window)
{
    __super::init(window);

    if (!glfwInit()) {

    }

    // Create a windowed mode window and its OpenGL context
    auto glwindow = glfwCreateWindow(window->width, window->height, "Triangle", NULL, NULL);
    window->set_native_window(glwindow);
    if (!window) {
        glfwTerminate();
    }

    bool bIsWindowFocused = true;

    glfwSetWindowUserPointer(glwindow, window);

    // Make the window's context current
    glfwMakeContextCurrent(glwindow);
    glfwSetInputMode(glwindow, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
    // Initialize GLEW
    glewExperimental = true;

    if (glewInit() != GLEW_OK) {
    }
    glEnable(GL_DEPTH_TEST);

    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
    /* Initialize the library */
    glfwSetWindowSizeCallback(glwindow, on_window_size_callback);
   /* glfwSetKeyCallback(glWindow, on_key_callback);
    glfwSetScrollCallback(glWindow, on_scroll_callback);
    
    glfwSetWindowCloseCallback(glWindow, on_window_close_callback);*/
    return true;
}




void OpenGlContext::pre_render()
{
    glViewport(0, 0, window->width, window->height);
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGlContext::post_render()
{
    glfwPollEvents();
    glfwSwapBuffers((GLFWwindow*)window->get_native_window());
}

void OpenGlContext::end()
{
    glfwDestroyWindow((GLFWwindow*)window->get_native_window());
    glfwTerminate();
}