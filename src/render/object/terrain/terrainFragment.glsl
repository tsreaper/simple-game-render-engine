#version 400 core

in vec2 passCoord;
in vec3 vertexNorm;
in vec3 toCameraVec;
in vec3 toLightVec[8];

out vec4 pixel;

uniform sampler2D textureK;
uniform sampler2D textureR;
uniform sampler2D textureG;
uniform sampler2D textureB;
uniform sampler2D blendMap;

uniform vec3 lightCol[8];
uniform vec3 lightAttenuation[8];

uniform vec3 skyCol;

const float FOG_DENSITY = 0.003;
const float FOG_GRADIENT = 5.5;

float calcAttenuation(vec3 fac, float dis)
{
    return fac.x + fac.y * dis + fac.z * dis * dis;
}

void main(void)
{
    // Calculate terrain blend map
    vec4 blendMapCol = texture(blendMap, passCoord);
    float kFac = 1 - (blendMapCol.r + blendMapCol.g + blendMapCol.b);
    vec2 tiledCoords = passCoord * 40.0;
    vec4 kCol = texture(textureK, tiledCoords) * kFac;
    vec4 rCol = texture(textureR, tiledCoords) * blendMapCol.r;
    vec4 gCol = texture(textureG, tiledCoords) * blendMapCol.g;
    vec4 bCol = texture(textureB, tiledCoords) * blendMapCol.b;

    // Calculate light
    vec3 unitNorm = normalize(vertexNorm);
    vec3 unitCamera = normalize(toCameraVec);

    vec3 unitLight[8];
    for (int i = 0; i < 8; i++)
        unitLight[i] = normalize(toLightVec[i]);

    vec3 diffuse = vec3(0, 0, 0);
    for (int i = 0; i < 8; i++)
    {
        float dis = length(toLightVec[i]);
        float attenuation = calcAttenuation(lightAttenuation[i], dis);
        diffuse += dot(unitNorm, unitLight[i])/attenuation * lightCol[i];
    }
    diffuse = max(diffuse, 0.2);

    pixel = vec4(diffuse, 1.0) * (kCol + rCol + gCol + bCol);

    // Calculate fog
    float dis = length(toCameraVec.xyz);
    float visibility = exp(-pow(dis*FOG_DENSITY, FOG_GRADIENT));
    visibility = clamp(visibility, 0.0, 1.0);
    pixel = mix(vec4(skyCol, 1.0), pixel, visibility);
}
