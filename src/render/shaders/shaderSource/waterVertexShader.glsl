#version 400 core

in vec3 position;

uniform mat4 transMatrix;
uniform mat4 cameraMatrix;
uniform mat4 projMatrix;

uniform vec3 lightPos;

void main(void)
{
    vec4 worldCoord = transMatrix * vec4(position, 1.0);
    vec4 posToCam = cameraMatrix * worldCoord;
    
    gl_Position = projMatrix * posToCam;
}
