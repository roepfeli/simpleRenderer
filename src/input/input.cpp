#include <input.hpp>

#include <GLFW/glfw3.h>

// TODO: currently mousePosX, mousePosY are being used to
// set the rotation of the camera directly. This can lead to nasty
// floatingpoint inaccuracies when the player turns arround in one direction
// alot... fix this

// TODO: check if m_rot is used accordingly (perhaps it must be -m_rot, so
// that m_rot displays the actual rotations along x, y and z achsis)

static bool keyStates[512];
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

namespace input
{

void init(GLFWwindow* window)
{
    inputWindow = window;
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
}

bool isKeyPressed(int key)
{
    if (key < 0 || key >= 512)
    {
        return false;
    }

    return keyStates[key];
}

void update()
{
    glfwPollEvents();
}

float getMouseX()
{
    return mousePosX;
}

float getMouseY()
{
    return mousePosY;
}

float getMouseDX()
{
    return mousePosX - mousePosPrevX;
}
float getMouseDY()
{
    return mousePosY - mousePosPrevY;
}

} // namespace input