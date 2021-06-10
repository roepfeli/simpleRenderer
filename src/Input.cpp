#include <Input.hpp>

#include <GLFW/glfw3.h>

static bool keyStates[256];
static GLFWwindow* inputWindow;

static float mousePosPrevX = 0.0f;
static float mousePosPrevY = 0.0f;
static float mousePosX = 0.0f;
static float mousePosY = 0.0f;

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    keyStates[key] = (action == GLFW_PRESS || action == GLFW_REPEAT);
}

static void cursor_position_callback(GLFWwindow* window, double posX, double posY)
{
    mousePosPrevX = mousePosX;
    mousePosPrevY = mousePosY;
    mousePosX = posX;
    mousePosY = posY;
}

void Input::Init(GLFWwindow* window)
{
    inputWindow = window;
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
}

bool Input::IsKeyPressed(int key)
{
    if (key < 0 || key >= 256)
    {
        return false;
    }

    return keyStates[key];
}

void Input::Update()
{
    glfwPollEvents();
}

float Input::GetMouseX()
{
    return mousePosX;
}

float Input::GetMouseY()
{
    return mousePosY;
}

float Input::GetMouseDX()
{
    return mousePosX - mousePosPrevX;
}
float Input::GetMouseDY()
{
    return mousePosY - mousePosPrevY;
}
