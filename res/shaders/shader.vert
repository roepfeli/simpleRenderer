#version 300 es

uniform mat4 u_mvp;
uniform mat4 u_model;

uniform mat4 u_useOwn;

// TODO: change to vec4 if it is safe to do so...
layout(location = 0) in vec4 position;
layout(location = 1) in vec2 tex;
layout(location = 2) in vec3 normal;

out vec2 texCoord;
out vec3 normalCoord;
out vec3 fragPos;

void main ()
{
  gl_Position = u_mvp * position;

  texCoord = tex;

  int useOwn = int(u_useOwn);

  if (useOwn == 1)
  {
    // muh way of doing things:
    mediump vec3 worldSpacePosition = vec3(u_model * position);
    mediump vec3 worldSpaceNormalExtention = vec3(u_model * (vec4(normal, 1.0) + position));
    normalCoord = worldSpaceNormalExtention - worldSpacePosition;
  }

  else
  {
    // tutorials way of doing things:
    normalCoord = mat3(transpose(inverse(u_model))) * normal;
  }

  fragPos = vec3(u_model * position);
}