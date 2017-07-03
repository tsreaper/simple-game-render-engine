#version 400 core

in vec2 passCoord;
in vec3 vertexNorm;
in vec3 toCameraVec;
in vec3 toLightVec[8];

out vec4 pixel;

uniform sampler2D textureSampler;

uniform vec3 lightCol[8];
uniform vec3 lightAttenuation[8];

uniform float reflectivity;
uniform float shineDamper;

uniform vec3 skyCol;

const float FOG_DENSITY = 0.003;
const float FOG_GRADIENT = 5.5;

float calcAttenuation(vec3 fac, float dis)
{
    return fac.x + fac.y * dis + fac.z * dis * dis;
}

void main(void)
{
    // Discard object's transparent part
    vec4 textureCol = texture(textureSampler, passCoord);
    if (textureCol.a < 0.5)
    {
        discard;
    }

    // Calculate light color
    vec3 unitNorm = normalize(vertexNorm);
    vec3 unitCamera = normalize(toCameraVec);

    vec3 unitLight[8];
    for (int i = 0; i < 8; i++)
        unitLight[i] = normalize(toLightVec[i]);

    vec3 diffuse = vec3(0, 0, 0);
    vec3 specular = vec3(0, 0, 0);
    for (int i = 0; i < 8; i++)
    {
        float dis = length(toLightVec[i]);
        float attenuation = calcAttenuation(lightAttenuation[i], dis);

        diffuse += max(dot(unitNorm, unitLight[i]), 0.0)/attenuation * lightCol[i];

        vec3 reflectDir = reflect(-unitLight[i], unitNorm);
        specular += pow(max(dot(reflectDir, unitCamera)/attenuation, 0.0), shineDamper) * reflectivity * lightCol[i];
    }
    diffuse = max(diffuse, 0.2);

    pixel = vec4(diffuse, 1.0) * textureCol + vec4(specular, 1.0);

    // Calculate fog
    float dis = length(toCameraVec.xyz);
    float visibility = exp(-pow(dis*FOG_DENSITY, FOG_GRADIENT));
    visibility = clamp(visibility, 0.0, 1.0);
    pixel = mix(vec4(skyCol, 1.0), pixel, visibility);
}
