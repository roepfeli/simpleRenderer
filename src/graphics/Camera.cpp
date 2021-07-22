#include <Camera.hpp>

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace graphics
{

glm::mat4 Camera::getCameraRotationMatrix()
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

void Camera::movePosition(const glm::vec3& movement)
{
    m_pos += movement;
}

void Camera::moveAlongDirection(const glm::vec3& movement)
{
    glm::vec4 movement4D = {movement.x, movement.y, movement.z, 1.0f};

    glm::vec4 other = glm::inverse(this->getCameraRotationMatrix()) * movement4D;

    m_pos.x += other.x;
    m_pos.y += other.y;
    m_pos.z += other.z;
}
glm::mat4 Camera::getViewMatrix()
{
    return glm::translate(this->getCameraRotationMatrix(), -m_pos);
};

glm::mat4 Camera::getPerspective()
{
    return m_perspective;
}

} // namespace graphics