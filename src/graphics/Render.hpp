#pragma once

#include "Camera.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"
#include "Texture.hpp"

namespace Render
{

void draw(Mesh& mesh, Texture& texture, Shader& shader, const glm::mat4& mvp);

} // namespace Render
