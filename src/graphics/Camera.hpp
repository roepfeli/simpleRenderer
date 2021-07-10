#pragma once

#include <glm/glm.hpp>

namespace graphics
{

class Camera
{
private:
    glm::mat4 getCameraRotationMatrix();
    glm::mat4 m_perspective;

public:
    glm::vec3 m_pos;
    glm::vec3 m_rot;

    Camera(float fov, float ratio, float fnear, float ffar);

    void movePosition(glm::vec3& movement);
    void moveAlongDirection(glm::vec3& movement);
    glm::mat4 getViewMatrix();

    glm::mat4 getPerspective();
};

} // namespace graphics