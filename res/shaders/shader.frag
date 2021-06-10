#version 300 es


uniform sampler2D u_texture;

in mediump vec2 texCoord;

layout(location = 0) out mediump vec4 color;

void main ()
{
  color = texture(u_texture, texCoord);
}