#version 400 core

in vec3 position;
in vec2 textureCoord;
in vec3 norm;

out vec2 passCoord;
out vec3 vertexNorm;
out vec3 toCameraVec;
out vec3 toLightVec[8];

uniform mat4 transMatrix;
uniform mat4 cameraMatrix;
uniform mat4 projMatrix;

uniform vec3 lightPos[8];

uniform float clipHeight;
uniform float clipPositive;

void main(void)
{
    vec4 worldCoord = transMatrix * vec4(position, 1.0);

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

    passCoord = textureCoord;
    vertexNorm = (transMatrix * vec4(norm, 0.0)).xyz;
    toCameraVec = (inverse(cameraMatrix) * vec4(0.0, 0.0, 0.0, 1.0) - worldCoord).xyz;

    for (int i = 0; i < 8; i++)
        toLightVec[i] = lightPos[i] - worldCoord.xyz;
}
