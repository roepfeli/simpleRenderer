#pragma once

#include "../include/Camera.hpp"
#include "../include/Mesh.hpp"
#include "../include/Shader.hpp"
#include "../include/Texture.hpp"

namespace Render
{

void draw(Mesh& mesh, Texture& texture, Shader& shader, const glm::mat4& mvp);

} // namespace Render
