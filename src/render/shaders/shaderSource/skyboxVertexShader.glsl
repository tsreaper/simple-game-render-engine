#version 400 core

in vec3 position;

out vec3 passCoord;

uniform mat4 transMatrix;
uniform mat4 cameraMatrix;
uniform mat4 projMatrix;

const float SIZE = 500;

void main(void)
{
    vec4 worldCoord = transMatrix * vec4(position, 1.0);
    vec4 posToCam = cameraMatrix * worldCoord;
    
    gl_Position = projMatrix * posToCam;
    
    passCoord = position / SIZE;
}
