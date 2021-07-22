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

    float ratio = display.getRatio();

    Camera camera(75.0f, ratio, 0.003f, 1000.0f);

    camera.movePosition(glm::vec3(0.0f, 0.0f, 0.0f));

    glClearColor(0.0f, 0.15f, 0.3f, 1.0f);

    // glFrontFace(GL_CCW);
    // glCullFace(GL_BACK);
    // glEnable(GL_CULL_FACE);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LESS);

    Mesh meshCoordinateSystem("res/objects/coordinate_system.obj");
    Mesh meshTeapot("res/objects/teapot.obj");

    Texture texture("res/textures/marble.jpg");
    Shader shader("res/shaders/shader.vert", "res/shaders/shader.frag");

    size_t engine_tick = 0;

    glm::vec3 prev = camera.m_pos;

    float prevX, prevY;

    while (!display.shouldClose())
    {
        input::update();

        if (input::isKeyPressed(GLFW_KEY_ESCAPE))
        {
            display.requestClose();
        }

        if (input::isKeyPressed(GLFW_KEY_W))
        {
            camera.moveAlongDirection(glm::vec3(0.0f, 0.0f, -0.02f));
        }

        if (input::isKeyPressed(GLFW_KEY_A))
        {
            camera.moveAlongDirection(glm::vec3(-0.02f, 0.0f, 0.0f));
        }

        if (input::isKeyPressed(GLFW_KEY_S))
        {
            camera.moveAlongDirection(glm::vec3(0.0f, 0.0f, 0.02f));
        }

        if (input::isKeyPressed(GLFW_KEY_D))
        {
            camera.moveAlongDirection(glm::vec3(0.02f, 0.0f, 0.0f));
        }

        camera.m_rot.y = input::getMouseX() * 0.001f;
        camera.m_rot.x = input::getMouseY() * 0.001f * (640.0f / 480.0f);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // set light-uniforms: AMBIENT
        // TODO: perhabs abstract that away in the shader-class: shader.setAmbientColor(), shader.useAmbientColor()
        shader.bind();
        shader.setUniform3fv("u_ambientColor", glm::vec3(0.2f, 0.4f, 0.2f));
        shader.setUniform1f("u_ambientStrength", 1.0f);
        Shader::UnbindAll();

        // set light-uniforms: DIFFUSE
        // TODO: also abstract that away...

        // calculate diffuse-position: should go round in a circle
        // float radius = 100.0f;
        // float f = 0.02 * engine_tick;
        // float x = glm::cos(f) * radius;
        // float y = glm::cos(f) * radius;
        // float z = glm::sin(f) * radius;

        // set light-uniforms: SPECULAR
        // TODO: also abstract that away...
        shader.bind();
        shader.setUniform3fv("u_cameraPosition", camera.m_pos);
        shader.setUniform1f("u_specularStrength", 2.0f);
        Shader::UnbindAll();

        shader.bind();
        // shader.setUniform3fv("u_diffusePosition", glm::vec3(x, y, z));
        shader.setUniform3fv("u_diffusePosition", glm::vec3(10.0f, 10.0f, 10.0f));
        shader.setUniform3fv("u_diffuseColor", glm::vec3(1.0f, 1.0f, 1.0f));
        Shader::UnbindAll();

        glm::mat4 modelTeapot = glm::translate(glm::mat4(1.0f), glm::vec3(2.5f, 2.5f, 2.5f));
        glm::mat4 modelCoordinateSystem = glm::mat4(1.0f);

        if (prev != camera.m_pos)
        {
            std::cout << "x: " << camera.m_pos.x << " ";
            std::cout << "y: " << camera.m_pos.y << " ";
            std::cout << "z: " << camera.m_pos.z << "\n";

            prev = camera.m_pos;
        }

        render::draw(meshTeapot,
                     texture,
                     shader,
                     modelTeapot,
                     camera.getViewMatrix(),
                     camera.getPerspective());

        render::draw(meshCoordinateSystem,
                     texture,
                     shader,
                     modelCoordinateSystem,
                     camera.getViewMatrix(),
                     camera.getPerspective());

        display.present();

        ++engine_tick;
    }

    return 0;
}
