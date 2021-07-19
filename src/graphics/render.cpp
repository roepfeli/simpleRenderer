#include <Camera.hpp>
#include <render.hpp>

#include <glm/mat4x4.hpp>

#include <GL/glew.h>

namespace graphics::render
{

void draw(Mesh& mesh,
          Texture& texture,
          Shader& shader,
          const glm::mat4& model,
          const glm::mat4& view,
          const glm::mat4& perspective)
{
    // bind given data
    mesh.bind();
    texture.bind(0);
    shader.bind();

    // TODO: for now just use TEXTURE0 every time...
    shader.setUniform1i("u_texture", 0);

    // upload uniform values
    shader.setUniformMatrix4fv("u_mvp", perspective * (view * model));
    shader.setUniformMatrix4fv("u_model", model);

    // specify vertex-layout
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(
        1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)(sizeof(float) * 3));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(
        2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)(sizeof(float) * 5));

    // actually draw verticies
    // TODO replace with glDrawElements for index-buffer
    glDrawArrays(GL_TRIANGLES, 0, mesh.getVerticies().size());

    // unbind all data
    Mesh::unbindAll();
    Texture::unbindAll();
    Shader::UnbindAll();
}

} // namespace graphics::render