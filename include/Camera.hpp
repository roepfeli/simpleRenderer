#pragma once

#include <glm/glm.hpp>

class Camera
{
private:
    glm::mat4 GetCameraRotMat();
    glm::mat4 m_perspective;

public:
    glm::vec3 m_pos;
    glm::vec3 m_rot;

    Camera(float fov, float ratio, float fnear, float ffar);

    void MovePos(glm::vec3& movement);
    void MoveAlongDir(glm::vec3& movement);
    glm::mat4 GetViewMatrix();

    glm::mat4 GetPerspective();
};
