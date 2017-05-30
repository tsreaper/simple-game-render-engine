#version 400 core

in vec3 position;

out vec3 passCoord;

uniform mat4 transMatrix;
uniform mat4 cameraMatrix;
uniform mat4 projMatrix;

uniform float clipHeight;
uniform float clipPositive;

const float SIZE = 500;

void main(void)
{
    vec4 worldCoord = transMatrix * vec4(SIZE*position, 1.0);

    if (clipPositive > 0.5)
    {
        gl_ClipDistance[0] = clipHeight - worldCoord.y;
    }
    else
    {
        gl_ClipDistance[0] = worldCoord.y - clipHeight;
    }

    vec4 posToCam = cameraMatrix * worldCoord;

    gl_Position = projMatrix * posToCam;

    passCoord = position;
}
