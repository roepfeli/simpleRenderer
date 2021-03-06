#include <Shader.hpp>

#include <iostream>
#include <vector>

#include <GL/glew.h>

#include <util.hpp>

static unsigned int CompileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, NULL);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);

    if (result == GL_FALSE)
    {
        int length;

        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char message[length];

        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile "
                  << ((type == GL_VERTEX_SHADER) ? ("vertex") : ("fragment")) << "-shader!"
                  << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

namespace graphics
{

Shader::Shader(const char* vertexShader, const char* fragmentShader)
{
    m_program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, util::loadAsString(vertexShader));
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, util::loadAsString(fragmentShader));

    glAttachShader(m_program, vs);
    glAttachShader(m_program, fs);
    glLinkProgram(m_program);
    glValidateProgram(m_program);

    glDeleteShader(vs);
    glDeleteShader(fs);
}

void Shader::bind()
{
    glUseProgram(m_program);
}

void Shader::UnbindAll()
{
    glUseProgram(0);
}

Shader::~Shader()
{
    glDeleteProgram(m_program);
}

void Shader::setUniformMatrix4fv(const std::string& name, const glm::mat4& matrix)
{
    int location = glGetUniformLocation(m_program, name.c_str());

    // if (location == -1)
    // {
    //     std::cout << "No Uniform named " << name << " found\n";
    // }

    glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]);
}

void Shader::setUniform1i(const std::string& name, int value)
{
    int location = glGetUniformLocation(m_program, name.c_str());

    // if (location == -1)
    // {
    //     std::cout << "No Uniform named " << name << " found\n";
    // }

    glUniform1i(location, value);
}

void Shader::setUniform3f(const std::string& name, const glm::vec3& vector)
{
    int location = glGetUniformLocation(m_program, name.c_str());

    // if (location == -1)
    // {
    //     std::cout << "No Uniform named " << name << " found\n";
    // }

    glUniform3f(location, vector[0], vector[1], vector[2]);
}

void Shader::setUniform3fv(const std::string& name, const std::vector<glm::vec3>& vectors)
{
    int location = glGetUniformLocation(m_program, name.c_str());

    if (location == -1)
    {
        std::cout << "No Uniform named " << name << " found\n";
    }

    glUniform3fv(location, vectors.size(), &vectors[0][0]);
}

void Shader::setUniform1f(const std::string& name, float value)
{
    int location = glGetUniformLocation(m_program, name.c_str());

    if (location == -1)
    {
        std::cout << "No Uniform named " << name << " found\n";
    }

    glUniform1f(location, value);
}

} // namespace graphics