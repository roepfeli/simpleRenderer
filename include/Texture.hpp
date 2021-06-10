#pragma once

#include <string>

class Texture
{
public:
    Texture(const std::string& pathToTexture);
    ~Texture();

    void bind(unsigned int slot = 0) const;
    static void unbindAll(unsigned int slot = 0);

    inline int getWidth() const
    {
        return m_width;
    }
    inline int getHeight() const
    {
        return m_height;
    }

private:
    unsigned int m_textureID;
    std::string m_pathToTexture;
    int m_width, m_height, m_BPP;

    uint8_t* m_localBuffer;
};