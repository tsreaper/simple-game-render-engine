#version 400 core

in vec2 passCoord;

out vec4 pixel;

uniform sampler2D reflection;

uniform vec3 lightCol;

void main(void)
{
    pixel = texture(reflection, passCoord);
}
