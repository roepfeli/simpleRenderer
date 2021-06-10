#include <Texture.hpp>

#include <stb_image.h>

#include <GL/glew.h>

Texture::Texture(const std::string& pathToTexture)
    : m_textureID(0)
    , m_pathToTexture(pathToTexture)
    , m_width(0)
    , m_height(0)
    , m_BPP(0)
    , m_localBuffer(nullptr)
{

    stbi_set_flip_vertically_on_load(1);
    m_localBuffer = stbi_load(pathToTexture.c_str(), &m_width, &m_height, &m_BPP, 4);

    glGenTextures(1, &m_textureID);
    glBindTexture(GL_TEXTURE_2D, m_textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(
        GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_localBuffer);
    glBindTexture(GL_TEXTURE_2D, 0);

    if (m_localBuffer)
    {
        free(m_localBuffer);
        m_localBuffer = nullptr;
    }
}

Texture::~Texture()
{
    glDeleteTextures(1, &m_textureID);

    if (m_localBuffer)
    {
        free(m_localBuffer);
        m_localBuffer = nullptr;
    }
}

void Texture::bind(unsigned int slot) const
{

    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_textureID);
}

void Texture::unbindAll(unsigned int slot)
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, 0);
}