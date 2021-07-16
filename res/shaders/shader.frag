#version 300 es


uniform sampler2D u_texture;
uniform mediump vec3 u_ambientColor;
uniform mediump float u_ambientStrength;

in mediump vec2 texCoord;

layout(location = 0) out mediump vec4 color;

void main ()
{
  mediump vec3 ambient = u_ambientStrength * u_ambientColor;
  color = texture(u_texture, texCoord) * vec4(ambient, 1.0);
}