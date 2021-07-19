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

#include <algorithm>
#include <iostream>
#include <string>

#include <thread>

using namespace graphics;

int main()
{
    Display display(640, 480, "SimpleRenderer");

    float ratio = display.m_width / (float)display.m_height;

    Camera camera(75.0f, ratio, 0.003f, 1000.0f);

    camera.movePosition(glm::vec3(2.0f, -2.0f, -5.0f));

    glClearColor(0.0f, 0.15f, 0.3f, 1.0f);

    // glFrontFace(GL_CCW);
    // glCullFace(GL_BACK);
    // glEnable(GL_CULL_FACE);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LESS);

    Mesh meshTeapot("res/objects/teapot.obj");

    Texture texture("res/textures/marble.jpg");
    Shader shader("res/shaders/shader.vert", "res/shaders/shader.frag");

    bool useOwnDiffuseLightNormalCalculation = false;

    size_t engine_tick = 0;

    while (!display.shouldClose())
    {
        input::update();

        if (input::isKeyPressed(GLFW_KEY_ESCAPE))
        {
            display.requestClose();
        }

        if (input::isKeyPressed(GLFW_KEY_W))
        {
            glm::vec3 tmp = glm::vec3(0.0f, 0.0f, 0.02f);
            camera.moveAlongDirection(tmp);
        }

        if (input::isKeyPressed(GLFW_KEY_F1))
        {
            std::cout << "Using own implementation\n";
            useOwnDiffuseLightNormalCalculation = true;
        }

        if (input::isKeyPressed(GLFW_KEY_F2))
        {
            std::cout << "Using own tutorial implementation\n";
            useOwnDiffuseLightNormalCalculation = false;
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

        // set light-uniforms: AMBIENT
        // TODO: perhabs abstract that away in the shader-class: shader.setAmbientColor(), shader.useAmbientColor()
        shader.bind();
        shader.setUniform3fv("u_ambientColor", glm::vec3(0.2f, 0.4f, 0.5f));
        shader.setUniform1f("u_ambientStrength", 1.0f);
        Shader::UnbindAll();

        // set light-uniforms: DIFFUSE
        // TODO: also abstract that away...

        // calculate diffuse-position: should go round in a circle
        float radius = 100.0f;
        float f = 0.02 * engine_tick;
        float z = glm::sin(f) * radius;
        float x = glm::cos(f) * radius;

        shader.bind();
        shader.setUniform3fv("u_diffusePosition", glm::vec3(x, 0.0f, z));
        shader.setUniform3fv("u_diffuseColor", glm::vec3(1.0f, 1.0f, 1.0f));
        shader.setUniform1i("u_useOwn", useOwnDiffuseLightNormalCalculation);
        Shader::UnbindAll();

        glm::mat4 model = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f, 0.5f, 0.5f));

        render::draw(
            meshTeapot, texture, shader, model, camera.getViewMatrix(), camera.getPerspective());

        display.present();

        ++engine_tick;
    }

    return 0;
}
