#version 400 core

in vec3 position;
in vec2 textureCoord;
in vec3 norm;

out vec2 passCoord;
out vec3 vertexNorm;
out vec3 toLightVec;
out vec3 toCameraVec;
out float visibility;

uniform mat4 transMatrix;
uniform mat4 cameraMatrix;
uniform mat4 projMatrix;

uniform vec3 lightPos;

const float fogDensity = 0.003;
const float fogGradient = 5.5;

void main(void)
{
    vec4 worldCoord = transMatrix * vec4(position, 1.0);
    vec4 posToCam = cameraMatrix * worldCoord;
    
    gl_Position = projMatrix * posToCam;
    
    passCoord = textureCoord;
    vertexNorm = (transMatrix * vec4(norm, 0.0)).xyz;
    toLightVec = lightPos - worldCoord.xyz;
    toCameraVec = (inverse(cameraMatrix) * vec4(0.0, 0.0, 0.0, 1.0) - worldCoord).xyz;
    
    float dis = length(posToCam.xyz);
    visibility = exp(-pow(dis*fogDensity, fogGradient));
    visibility = clamp(visibility, 0.0, 1.0);
}
