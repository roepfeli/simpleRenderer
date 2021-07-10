#define GLM_ENABLE_EXPERIMENTAL

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x3.hpp>
#include <glm/vec3.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include <Camera.hpp>
#include <Display.hpp>
#include <Mesh.hpp>
#include <Shader.hpp>
#include <Texture.hpp>
#include <input.hpp>
#include <render.hpp>
#include <util.hpp>

#include <iostream>
#include <string>

#include <thread>

using namespace graphics;

int main()
{
    Display display(640, 480, "SimpleRenderer");

    float ratio = display.m_width / (float)display.m_height;

    Camera camera(75.0f, ratio, 0.003f, 1000.0f);

    std::cout << glGetString(GL_VERSION) << std::endl;

    glClearColor(0.0f, 0.15f, 0.3f, 1.0f);

    // glFrontFace(GL_CCW);
    // glCullFace(GL_BACK);
    // glEnable(GL_CULL_FACE);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LESS);

    Mesh meshTeapot("res/objects/teapot.obj");
    Mesh meshCube("res/objects/testcube.obj");

    Texture texture("res/textures/marble.jpg");
    Shader shader("res/shaders/shader.vert", "res/shaders/shader.frag");

    while (!display.shouldClose())
    {
        input::update();

        if (input::isKeyPressed(GLFW_KEY_Q))
        {
            display.requestClose();
        }

        if (input::isKeyPressed(GLFW_KEY_W))
        {
            glm::vec3 tmp = glm::vec3(0.0f, 0.0f, 0.02f);
            camera.moveAlongDirection(tmp);
        }

        if (input::isKeyPressed(GLFW_KEY_A))
        {
            glm::vec3 tmp = glm::vec3(0.02f, 0.0f, 0.0f);
            camera.moveAlongDirection(tmp);
        }

        if (input::isKeyPressed(GLFW_KEY_S))
        {
            glm::vec3 tmp = glm::vec3(0.0f, 0.0f, -0.02f);
            camera.moveAlongDirection(tmp);
        }

        if (input::isKeyPressed(GLFW_KEY_D))
        {
            glm::vec3 tmp = glm::vec3(-0.02f, 0.0f, 0.0f);
            camera.moveAlongDirection(tmp);
        }

        camera.m_rot.y = input::getMouseX() * 0.001f;
        camera.m_rot.x = input::getMouseY() * 0.001f * (640.0f / 480.0f);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 mvpTeapot =
            camera.getPerspective() *
            (camera.getViewMatrix() * glm::scale(glm::mat4(1.0f), glm::vec3(0.5, 0.5, 0.5)));

        glm::mat4 mvpCube = camera.getPerspective() *
                            (camera.getViewMatrix() *
                             glm::translate(glm::scale(glm::mat4(1.0f), glm::vec3(0.2, 0.2, 0.2)),
                                            glm::vec3(15, 15, 0)));

        render::draw(meshTeapot, texture, shader, mvpTeapot);
        render::draw(meshCube, texture, shader, mvpCube);

        display.present();
    }
}
