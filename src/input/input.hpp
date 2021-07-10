#pragma once

#include <GLFW/glfw3.h>

namespace input
{

void update();
void init(GLFWwindow* window);
//Vector2f GetMousePos ();
bool isKeyPressed(int key);

float getMouseX();
float getMouseY();

float getMouseDX();
float getMouseDY();

} // namespace input