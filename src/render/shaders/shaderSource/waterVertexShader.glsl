#version 400 core

in vec3 position;

out vec4 passCoord;
out vec2 dudvCoord;
out vec3 toCameraVec;

uniform mat4 transMatrix;
uniform mat4 cameraMatrix;
uniform mat4 projMatrix;

uniform vec3 lightPos;

const float SIZE = 1024;

void main(void)
{
    vec4 worldCoord = transMatrix * vec4(position, 1.0);
    vec4 posToCam = cameraMatrix * worldCoord;
    
    gl_Position = passCoord = projMatrix * posToCam;
    dudvCoord = position.xz/SIZE;
    toCameraVec = (inverse(cameraMatrix) * vec4(0.0, 0.0, 0.0, 1.0) - worldCoord).xyz;
}
