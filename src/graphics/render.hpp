#pragma once

#include <Camera.hpp>
#include <Mesh.hpp>
#include <Shader.hpp>
#include <Texture.hpp>

namespace graphics::render
{

void draw(Mesh& mesh,
          Texture& texture,
          Shader& shader,
          const glm::mat4& model,
          const glm::mat4& view,
          const glm::mat4& perspective);

} // namespace graphics::render
