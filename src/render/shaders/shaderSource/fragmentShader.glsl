#version 400 core

in vec2 passCoord;
in vec3 vertexNorm;
in vec3 toLightVec;

out vec4 pixel;

uniform sampler2D textureSampler;
uniform vec3 lightCol;

void main(void)
{
    float brightness = max(dot(normalize(vertexNorm), normalize(toLightVec)), 0.0);
    vec3 diffuse = brightness * lightCol;
    
    pixel = vec4(diffuse, 1.0) * texture(textureSampler, passCoord);
}
