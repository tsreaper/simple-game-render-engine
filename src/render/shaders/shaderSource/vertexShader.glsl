#version 400 core

in vec3 position;
in vec2 textureCoord;
in vec3 norm;

out vec2 passCoord;
out vec3 vertexNorm;
out vec3 toLightVec;

uniform mat4 transMatrix;
uniform mat4 cameraMatrix;
uniform mat4 projMatrix;
uniform vec3 lightPos;

void main(void)
{
    vec4 worldCoord = transMatrix * vec4(position, 1.0);
    
    gl_Position = projMatrix * cameraMatrix * worldCoord;
    
    passCoord = textureCoord;
    vertexNorm = (transMatrix * vec4(norm, 0.0)).xyz;
    toLightVec = lightPos - worldCoord.xyz;
}
