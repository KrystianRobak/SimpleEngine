#include "WindowManager.h"

GLFWwindow* WindowManager::window = nullptr;
int WindowManager::width = INITIAL_WIDTH;
int WindowManager::height = INITIAL_HEIGHT;
bool WindowManager::bIsFocused = true;
std::pair<float, float> WindowManager::mouseLocation = std::make_pair(0, 0);

GLFWwindow* WindowManager::GetWindow()
{
    if (!window) {
        if (!glfwInit()) {

        }

        // Create a windowed mode window and its OpenGL context
        window = glfwCreateWindow(width, height, "Triangle", NULL, NULL);
        if (!window) {
            glfwTerminate();
        }

        bool bIsWindowFocused = true;

        glfwSetWindowFocusCallback(window, WindowManager::focusCallback);
        // Make the window's context current
        glfwMakeContextCurrent(window);
        glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
        // Initialize GLEW
        glewExperimental = true;

        if (glewInit() != GLEW_OK) {
        }
        glEnable(GL_DEPTH_TEST);

        glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

        return window;
    }

    return window;
}


void WindowManager::focusCallback(GLFWwindow* window, int focused)
{
    if (focused == GLFW_TRUE)
        bIsFocused = true;
    else
        bIsFocused = false;
}