#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <Display.hpp>
#include <input.hpp>

namespace graphics
{

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

    input::init(m_window);
}

Display::~Display()
{
    glfwTerminate();
}

bool Display::shouldClose()
{
    return glfwWindowShouldClose(m_window) || m_close;
}

void Display::requestClose()
{
    m_close = true;
}

void Display::present()
{
    glfwSwapBuffers(m_window);
}

float Display::getRatio()
{
    return m_width / (float)m_height;
}

} // namespace graphics