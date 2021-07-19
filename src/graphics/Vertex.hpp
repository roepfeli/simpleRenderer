#pragma once

#include <iostream>

namespace graphics
{

struct Vertex
{
    float x, y, z;
    float u, v;
    float nx, ny, nz;

    inline friend std::ostream& operator<<(std::ostream& os, const Vertex& vertex)
    {
        os << "{\n\tposition: (" << vertex.x << "," << vertex.y << "," << vertex.z << ")";
        os << "\n\ttexture: (" << vertex.u << "," << vertex.v << ")";
        os << "\n\tnormal: (" << vertex.nx << "," << vertex.ny << "," << vertex.nz << ")\n}\n";

        return os;
    }
};

} // namespace graphics