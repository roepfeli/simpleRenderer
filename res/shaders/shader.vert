#version 300 es

uniform mat4 u_mvp;

// TODO: change to vec4 if it is safe to do so...
layout(location = 0) in vec4 position;
layout(location = 1) in vec2 tex;

out vec2 texCoord;


void main ()
{
  gl_Position = u_mvp * position;
  texCoord = tex;
}