#version 300 es


uniform sampler2D u_texture;

uniform mediump vec3 u_ambientColor;
uniform mediump float u_ambientStrength;

uniform mediump vec3 u_cameraPosition;
// TODO: right now, all specular calculations for the light-sources
// have only one specularStrength. You might want to change this in the future
uniform mediump float u_specularStrength;

// due to glsl being bitchy about variable length-arrays, arrays of type 3fv have size of 64
// TODO: for now only 64 lights per draw-call. This should be more then sufficient,
// still if bugs occur of not showing lighting correctly, it could be this limitation...
uniform mediump vec3 u_diffusePosition[64];
uniform mediump vec3 u_diffuseColor[64];
uniform mediump int u_numLightSources;

in mediump vec2 texCoord;
in mediump vec3 normalCoord;
in mediump vec3 fragPos;

layout(location = 0) out mediump vec4 color;

void main ()
{
  // ambient:
  mediump vec3 ambient = u_ambientStrength * u_ambientColor;

  // vector calculations used for all lightsources
  mediump vec3 normalized = normalize(normalCoord);
  mediump vec3 viewDir = normalize(u_cameraPosition - fragPos);

  mediump vec3 result = ambient;

  for (int i = 0; i < u_numLightSources; ++i)
  {
    // diffuse:
    mediump vec3 lightDir = normalize(u_diffusePosition[i] - fragPos);
    mediump float diff = max(dot(normalized, lightDir), 0.0);
    result += diff * u_diffuseColor[i];

    // specular:
    mediump vec3 reflectDir = reflect(-lightDir, normalized);
    mediump float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
    result += u_specularStrength * spec * u_diffuseColor[i];
  }


  color = texture(u_texture, texCoord) * vec4(result, 1.0);
}