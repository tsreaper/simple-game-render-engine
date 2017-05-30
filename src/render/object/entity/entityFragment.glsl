#version 400 core

in vec2 passCoord;
in vec3 vertexNorm;
in vec3 toLightVec;
in vec3 toCameraVec;

out vec4 pixel;

uniform sampler2D textureSampler;

uniform vec3 lightCol;

uniform float reflectivity;
uniform float shineDamper;

uniform vec3 skyCol;

const float FOG_DENSITY = 0.003;
const float FOG_GRADIENT = 5.5;

void main(void)
{
    vec4 textureCol = texture(textureSampler, passCoord);
    if (textureCol.a < 0.5)
    {
        discard;
    }

    vec3 unitNorm = normalize(vertexNorm);
    vec3 unitLight = normalize(toLightVec);
    vec3 unitCamera = normalize(toCameraVec);

    float brightness = max(dot(unitNorm, unitLight), 0.2);
    vec3 diffuse = brightness * lightCol;

    vec3 reflectDir = reflect(-unitLight, unitNorm);
    vec3 specular = pow(max(dot(reflectDir, unitCamera), 0.0), shineDamper) * reflectivity * lightCol;
    pixel = vec4(diffuse, 1.0) * textureCol + vec4(specular, 1.0);

    float dis = length(toCameraVec.xyz);
    float visibility = exp(-pow(dis*FOG_DENSITY, FOG_GRADIENT));
    visibility = clamp(visibility, 0.0, 1.0);
    pixel = mix(vec4(skyCol, 1.0), pixel, visibility);
}
