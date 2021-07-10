#pragma once

#include <GLFW/glfw3.h>

namespace Input
{
void Update();
void Init(GLFWwindow* window);
//Vector2f GetMousePos ();
bool IsKeyPressed(int key);

float GetMouseX();
float GetMouseY();

float GetMouseDX();
float GetMouseDY();
} // namespace Input
