#include <Camera.hpp>

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

glm::mat4 Camera::GetCameraRotMat()
{
    glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), m_rot.x, glm::vec3(1.0f, 0.0f, 0.0f));
    return glm::rotate(rotation, m_rot.y, glm::vec3(0.0f, 1.0f, 0.0f));
}

Camera::Camera(float fov, float ratio, float zNear, float zFar)
{
    m_perspective = glm::perspective(glm::radians(fov), ratio, zNear, zFar);
    m_pos = {0.0f, 0.0f, 0.0f};
    m_rot = {0.0f, 0.0f, 0.0f};
}

void Camera::MovePos(glm::vec3& movement)
{
    m_pos += movement;
}

void Camera::MoveAlongDir(glm::vec3& movement)
{
    glm::vec4 movement4D = {movement.x, movement.y, movement.z, 1.0f};

    glm::vec4 other = glm::inverse(this->GetCameraRotMat()) * movement4D;

    m_pos.x += other.x;
    m_pos.y += other.y;
    m_pos.z += other.z;
}
glm::mat4 Camera::GetViewMatrix()
{
    return glm::translate(this->GetCameraRotMat(), m_pos);
};

glm::mat4 Camera::GetPerspective()
{
    return m_perspective;
}
