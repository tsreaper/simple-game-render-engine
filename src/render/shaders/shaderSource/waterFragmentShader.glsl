#version 400 core

in vec4 passCoord;
in vec2 dudvCoord;
in vec3 toCameraVec;

out vec4 pixel;

uniform sampler2D reflection;
uniform sampler2D refraction;
uniform sampler2D dudvMap;
uniform float moveFac;

uniform vec3 lightCol;

const float dudvFac = 0.01;

void main(void)
{
    vec2 distortion = texture(dudvMap, vec2(dudvCoord.x + moveFac, dudvCoord.y + moveFac)).rg * dudvFac;
    float texX = clamp(passCoord.x/passCoord.w/2+0.5 + distortion.x, 0.001, 0.999);
    float texY = clamp(passCoord.y/passCoord.w/2+0.5 + distortion.y, 0.001, 0.999);
    vec4 reflectionCol = texture(reflection, vec2(texX, -texY));
    vec4 refractionCol = texture(refraction, vec2(texX, texY));
    
    float refractionFac = dot(vec3(0.0, 1.0, 0.0), normalize(toCameraVec));
    refractionFac = clamp(refractionFac, 0.2, 0.8);
    pixel = mix(reflectionCol, refractionCol, refractionFac);
}
