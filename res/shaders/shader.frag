#version 300 es


uniform sampler2D u_texture;
uniform mediump vec3 u_ambientColor;
uniform mediump float u_ambientStrength;

// TODO: for now only one u_diffusePosition...
// TODO: this must become an array to allow for multiple light-sources
uniform mediump vec3 u_diffusePosition;
// TODO: obviously the same for u_diffuseColor...
uniform mediump vec3 u_diffuseColor;

in mediump vec2 texCoord;
in mediump vec3 normalCoord;
in mediump vec3 fragPos;

layout(location = 0) out mediump vec4 color;

void main ()
{
  mediump vec3 ambient = u_ambientStrength * u_ambientColor;

  mediump vec3 normalized = normalize(normalCoord);
  mediump vec3 lightDir = normalize(u_diffusePosition - fragPos);

  mediump float diff = max(dot(normalized, lightDir), 0.0);

  mediump vec3 diffuse = diff * u_diffuseColor;

  mediump vec3 result = ambient + diffuse;

  color = texture(u_texture, texCoord) * vec4(result, 1.0);
}