#version 400 core

in vec2 passCoord;
in vec3 vertexNorm;
in vec3 toLightVec;
in vec3 toCameraVec;
in float visibility;

out vec4 pixel;

uniform sampler2D textureK;
uniform sampler2D textureR;
uniform sampler2D textureG;
uniform sampler2D textureB;
uniform sampler2D blendMap;

uniform vec3 lightCol;

uniform vec3 skyCol;

const float FOG_DENSITY = 0.003;
const float FOG_GRADIENT = 5.5;

void main(void)
{
    vec4 blendMapCol = texture(blendMap, passCoord);
    float kFac = 1 - (blendMapCol.r + blendMapCol.g + blendMapCol.b);
    vec2 tiledCoords = passCoord * 40.0;
    vec4 kCol = texture(textureK, tiledCoords) * kFac;
    vec4 rCol = texture(textureR, tiledCoords) * blendMapCol.r;
    vec4 gCol = texture(textureG, tiledCoords) * blendMapCol.g;
    vec4 bCol = texture(textureB, tiledCoords) * blendMapCol.b;
    
    vec3 unitNorm = normalize(vertexNorm);
    vec3 unitLight = normalize(toLightVec);
    vec3 unitCamera = normalize(toCameraVec);
    
    float brightness = max(dot(unitNorm, unitLight), 0.2);
    vec3 diffuse = brightness * lightCol;
    pixel = vec4(diffuse, 1.0) * (kCol + rCol + gCol + bCol);
    
    float dis = length(toCameraVec.xyz);
    float visibility = exp(-pow(dis*FOG_DENSITY, FOG_GRADIENT));
    visibility = clamp(visibility, 0.0, 1.0);
    pixel = mix(vec4(skyCol, 1.0), pixel, visibility);
}
