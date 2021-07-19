#pragma once

#include <string>
#include <vector>

#include <Vertex.hpp>

namespace graphics
{

class Mesh
{

private:
    unsigned int m_vbo;
    std::vector<Vertex> m_verticies;
    std::string m_pathToObject;

protected:
public:
    Mesh(const std::string& pathToObject);
    ~Mesh();

    std::vector<Vertex>& getVerticies();
    void bind();
    static void unbindAll();
};

} // namespace graphics