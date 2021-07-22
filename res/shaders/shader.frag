#version 300 es


uniform sampler2D u_texture;
uniform mediump vec3 u_ambientColor;
uniform mediump float u_ambientStrength;
uniform mediump vec3 u_cameraPosition;
uniform mediump float u_specularStrength;

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
  // ambient:
  mediump vec3 ambient = u_ambientStrength * u_ambientColor;

  // diffuse:
  mediump vec3 normalized = normalize(normalCoord);
  mediump vec3 lightDir = normalize(u_diffusePosition - fragPos);
  mediump float diff = max(dot(normalized, lightDir), 0.0);
  mediump vec3 diffuse = diff * u_diffuseColor;

  // specular:
  mediump vec3 viewDir = normalize(u_cameraPosition - fragPos);
  mediump vec3 reflectDir = reflect(-lightDir, normalized);
  mediump float spec = pow(max(dot(viewDir, reflectDir), 0.0), 64.0);
  mediump vec3 specular = u_specularStrength * spec * u_diffuseColor;

  mediump vec3 result = ambient + diffuse + specular;

  color = texture(u_texture, texCoord) * vec4(result, 1.0);
}