#pragma once

#include <GLFW/glfw3.h>

namespace graphics
{

class Display
{
private:
    GLFWwindow* m_window;
    bool m_close;

public:
    const size_t m_width, m_height;
    const char* m_name;

public:
    Display(size_t width, size_t height, const char* name);
    ~Display();

    bool shouldClose();
    void present();
    void requestClose();
    float getRatio();
};

} // namespace graphics