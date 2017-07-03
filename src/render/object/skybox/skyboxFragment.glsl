#version 400 core

in vec3 passCoord;

out vec4 pixel;

uniform samplerCube textureDay;
uniform samplerCube textureNight;
uniform float nightFac;
uniform vec3 skyCol;

const float LOWER = 0;
const float UPPER = 0.3;

void main(void)
{
    // Mix day/night texture
    pixel = mix(texture(textureDay, passCoord), texture(textureNight, passCoord), nightFac);

    // Calculate fog
    float fogFac = (passCoord.y - LOWER) / (UPPER - LOWER);
    fogFac = clamp(fogFac, 0.0, 1.0);
    pixel = mix(vec4(skyCol, 1.0), pixel, fogFac);
}
