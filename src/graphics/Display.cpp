#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Display.hpp"
#include <Input.hpp>

Display::Display(const size_t width, const size_t height, const char* name)
    : m_width(width)
    , m_height(height)
{
    m_name = name;

    m_close = false;

    glfwInit();
    m_window = glfwCreateWindow(width, height, name, NULL, NULL);
    glfwMakeContextCurrent(m_window);

    glewInit();

    Input::Init(m_window);
}

Display::~Display()
{
    glfwTerminate();
}

bool Display::ShouldClose()
{
    return glfwWindowShouldClose(m_window) || m_close;
}

void Display::RequestClose()
{
    m_close = true;
}

void Display::Present()
{
    glfwSwapBuffers(m_window);
}
