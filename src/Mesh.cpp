#include "../include/Mesh.hpp"
#include "../include/Util.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include <GL/glew.h>

// DEBUG
template <typename T>
static void printVector(std::vector<T> vec)
{
    std::cout << "[";

    for (T i : vec)
    {
        std::cout << i << ",";
    }

    if (vec.size() > 0)
    {
        std::cout << "\b";
    }

    std::cout << "]\n";
}

enum LineType
{
    VERTEX_POS,
    TEXTURE_COORD,
    FACE,
    UNDEFINED
};

struct vertexPos
{
    float x, y, z;
};

struct texturePos
{
    float u, v;
};

struct vertexIndexData
{
    size_t vert1;
    size_t vert2;
    size_t vert3;

    size_t tex1;
    size_t tex2;
    size_t tex3;
};

static LineType getLineType(std::string& line)
{
    if (line.size() >= 3)
    {
        // v
        if (line[0] == 'v' && line[1] == ' ')
        {
            return VERTEX_POS;
        }
        // vt
        if (line[0] == 'v' && line[1] == 't' && line[2] == ' ')
        {
            return TEXTURE_COORD;
        }
        // f
        if (line[0] == 'f' && line[1] == ' ')
        {
            return FACE;
        }
    }

    return UNDEFINED;
}

static vertexPos processVertexPos(std::string& line)
{
    std::vector<std::string> numbers = Util::splitString(line, ' ');
    vertexPos position;

    position.x = atof(numbers[1].c_str());
    position.y = atof(numbers[2].c_str());
    position.z = atof(numbers[3].c_str());

    return position;
}

static texturePos processTexturePos(std::string& line)
{
    std::vector<std::string> numbers = Util::splitString(line, ' ');

    texturePos position;

    position.u = atof(numbers[1].c_str());
    position.v = atof(numbers[2].c_str());

    return position;
}

static vertexIndexData processFace(std::string& line)
{
    std::vector<std::string> numbers = Util::splitString(line, ' ');

    vertexIndexData vid;

    auto numbers1 = Util::splitString(numbers[1], '/');
    vid.vert1 = atoi(numbers1[0].c_str()) - 1;
    vid.tex1 = atoi(numbers1[1].c_str()) - 1;

    auto numbers2 = Util::splitString(numbers[2], '/');
    vid.vert2 = atoi(numbers2[0].c_str()) - 1;
    vid.tex2 = atoi(numbers2[1].c_str()) - 1;

    auto numbers3 = Util::splitString(numbers[3], '/');
    vid.vert3 = atoi(numbers3[0].c_str()) - 1;
    vid.tex3 = atoi(numbers3[1].c_str()) - 1;

    return vid;
}

Mesh::Mesh(const std::string& pathToObj)
{
    m_pathToObj = pathToObj;

    // TODO: put mesh-loading in Util.cpp...
    std::ifstream inputStream(pathToObj.c_str());

    std::string line;

    std::vector<vertexPos> vertexPositions;
    std::vector<texturePos> texturePositions;

    // TODO: this is retarded and needs optimaziaitnaont...
    // for now no index-buffers...

    vertexIndexData vid;
    Vertex vert1, vert2, vert3;

    while (std::getline(inputStream, line))
    {
        switch (getLineType(line))
        {
        case VERTEX_POS:
            vertexPositions.push_back(processVertexPos(line));
            break;
        case TEXTURE_COORD:
            texturePositions.push_back(processTexturePos(line));
            break;
        case FACE:
            vid = processFace(line);

            vert1.x = vertexPositions[vid.vert1].x;
            vert1.y = vertexPositions[vid.vert1].y;
            vert1.z = vertexPositions[vid.vert1].z;
            vert1.u = texturePositions[vid.tex1].u;
            vert1.v = texturePositions[vid.tex1].v;

            vert2.x = vertexPositions[vid.vert2].x;
            vert2.y = vertexPositions[vid.vert2].y;
            vert2.z = vertexPositions[vid.vert2].z;
            vert2.u = texturePositions[vid.tex2].u;
            vert2.v = texturePositions[vid.tex2].v;

            vert3.x = vertexPositions[vid.vert3].x;
            vert3.y = vertexPositions[vid.vert3].y;
            vert3.z = vertexPositions[vid.vert3].z;
            vert3.u = texturePositions[vid.tex3].u;
            vert3.v = texturePositions[vid.tex3].v;

            m_verticies.push_back(vert1);
            m_verticies.push_back(vert2);
            m_verticies.push_back(vert3);

            break;
        case UNDEFINED:
            break;
        }
    }

    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

    glBufferData(GL_ARRAY_BUFFER,
                 m_verticies.size() * sizeof(Vertex),
                 (void*)m_verticies.data(),
                 GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Mesh::~Mesh()
{
    glDeleteBuffers(1, &m_vbo);
}

std::vector<Vertex>& Mesh::getVerticies()
{
    return m_verticies;
}
void Mesh::bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
}
void Mesh::unbindAll()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}