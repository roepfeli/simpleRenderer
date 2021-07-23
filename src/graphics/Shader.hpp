#pragma once

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

#include <string>
#include <vector>

namespace graphics
{

class Shader
{
private:
    unsigned int m_program;

public:
    Shader(const char* vertexShader, const char* fragmentShader);
    ~Shader();

    void setUniformMatrix4fv(const std::string& name, const glm::mat4& matrix);

    void setUniform1i(const std::string& name, int value);

    void setUniform3f(const std::string& name, const glm::vec3& vector);

    void setUniform1f(const std::string& name, float value);

    void setUniform3fv(const std::string& name, const std::vector<glm::vec3>& vectors);

    void bind();

    static void UnbindAll();
};

} // namespace graphics