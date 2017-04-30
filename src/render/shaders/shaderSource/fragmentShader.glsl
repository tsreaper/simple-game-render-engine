#version 400 core

in vec2 passCoord;
in vec3 vertexNorm;
in vec3 toLightVec;
in vec3 toCameraVec;

out vec4 pixel;

uniform sampler2D textureSampler;

uniform vec3 lightCol;

uniform float reflectivity;
uniform float shineDamper;

void main(void)
{
    vec3 unitNorm = normalize(vertexNorm);
    vec3 unitLight = normalize(toLightVec);
    vec3 unitCamera = normalize(toCameraVec);
    
    float brightness = max(dot(unitNorm, unitLight), 0.1);
    vec3 diffuse = brightness * lightCol;
    
    vec3 reflectDir = reflect(-unitLight, unitNorm);
    vec3 specular = pow(max(dot(reflectDir, unitCamera), 0.0), shineDamper) * reflectivity * lightCol;
    
    pixel = vec4(diffuse, 1.0) * texture(textureSampler, passCoord) + vec4(specular, 1.0);
}
