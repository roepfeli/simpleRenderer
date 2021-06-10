#pragma once

#include <glm/mat4x4.hpp>
#include <string>

class Shader
{
private:
    unsigned int m_program;

public:
    Shader(const char* vertexShader, const char* fragmentShader);
    ~Shader();

    void setUniformMatrix4fv(const std::string& name, const glm::mat4& matrix);

    void setUniform1i(const std::string& name, int value);

    void bind();

    static void UnbindAll();
};
