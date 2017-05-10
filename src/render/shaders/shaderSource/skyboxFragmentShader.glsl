#version 400 core

in vec3 passCoord;

out vec4 pixel;

uniform samplerCube textureSampler;
uniform vec3 skyCol;

const float lower = 0.0;
const float upper = 0.15;

void main(void)
{
    float fac = (passCoord.y - lower) / (upper-lower);
    fac = clamp(fac, 0.0, 1.0);
    
    pixel = texture(textureSampler, passCoord);
    pixel = mix(vec4(skyCol, 1.0), pixel, fac);
}
