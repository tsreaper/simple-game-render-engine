#version 400 core

in vec4 passCoord;
in vec2 texCoord;
in vec3 toLightVec;
in vec3 toCameraVec;

out vec4 pixel;

uniform sampler2D reflection;
uniform sampler2D refraction;
uniform sampler2D dudvMap;
uniform sampler2D normMap;
uniform float moveFac;

uniform vec3 lightCol;

uniform vec3 skyCol;

const float WAVE_STRENGTH = 0.01;

const float FOG_DENSITY = 0.003;
const float FOG_GRADIENT = 5.5;

const float REFLECTIVITY = 0.3;
const float SHINE_DAMPER = 10;

void main(void)
{
    vec2 biasedCoord = texture(dudvMap, vec2(texCoord.x + moveFac, texCoord.y)).rg * 0.1;
    biasedCoord = texCoord + vec2(biasedCoord.x ,biasedCoord.y + moveFac);
    vec2 distortion = (texture(dudvMap, biasedCoord).rg*2-1) * WAVE_STRENGTH;
    float texX = clamp(passCoord.x/passCoord.w/2+0.5 + distortion.x, 0.001, 0.999);
    float texY = clamp(passCoord.y/passCoord.w/2+0.5 + distortion.y, 0.001, 0.999);
    vec4 reflectionCol = texture(reflection, vec2(texX, -texY));
    vec4 refractionCol = texture(refraction, vec2(texX, texY));
    vec3 normCol = texture(normMap, biasedCoord).rgb;
    vec3 norm = vec3(normCol.r*2-1, normCol.b, normCol.g*2-1);
    vec3 unitNorm = normalize(norm);
    vec3 unitLight = normalize(toLightVec);
    vec3 unitCamera = normalize(toCameraVec);
    
    float refractionFac = dot(vec3(0.0, 1.0, 0.0), unitCamera);
    pixel = mix(reflectionCol, refractionCol, refractionFac);
    pixel = mix(pixel, vec4(0.0, 0.3, 0.5, 1.0), 0.2);
    
    float brightness = max(dot(unitNorm, unitLight), 0.2);
    vec3 diffuse = brightness * lightCol;
    
    vec3 reflectDir = reflect(-unitLight, unitNorm);
    vec3 specular = pow(max(dot(reflectDir, unitCamera), 0.0), SHINE_DAMPER) * REFLECTIVITY * lightCol;
    pixel = vec4(diffuse, 1.0) * pixel + vec4(specular, 1.0);
    
    float dis = length(toCameraVec.xyz);
    float visibility = exp(-pow(dis*FOG_DENSITY, FOG_GRADIENT));
    visibility = clamp(visibility, 0.0, 1.0);
    pixel = mix(vec4(skyCol, 1.0), pixel, visibility);
}
