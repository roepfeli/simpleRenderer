#pragma once

#include <string>
#include <vector>

struct Vertex
{
    float x, y, z;
    float u, v;
};

class Mesh
{

private:
    unsigned int m_vbo;
    std::vector<Vertex> m_verticies;
    std::string m_pathToObj;

protected:
public:
    Mesh(const std::string& pathToObj);
    ~Mesh();

    std::vector<Vertex>& getVerticies();
    void bind();
    static void unbindAll();
};
