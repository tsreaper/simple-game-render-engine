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
uniform sampler2D depthMap;
uniform float moveFac;

uniform vec3 lightCol;

uniform vec3 skyCol;

const float WAVE_STRENGTH = 0.04;

const float FOG_DENSITY = 0.003;
const float FOG_GRADIENT = 5.5;

const float Z_NEAR = 0.1;
const float Z_FAR = 1000.0;

const float REFLECTIVITY = 0.5;
const float SHINE_DAMPER = 20;

float parseDepth(float depth)
{
    return Z_NEAR*Z_FAR*2 / (Z_FAR+Z_NEAR - (depth*2-1)*(Z_FAR-Z_NEAR));
}

void main(void)
{
    vec2 biasedCoord = texture(dudvMap, vec2(texCoord.x + moveFac, texCoord.y)).rg * 0.1;
    biasedCoord = texCoord + vec2(biasedCoord.x ,biasedCoord.y + moveFac);
    vec2 distortion = (texture(dudvMap, biasedCoord).rg*2-1) * WAVE_STRENGTH;
    float texX = passCoord.x/passCoord.w/2+0.5;
    float texY = passCoord.y/passCoord.w/2+0.5;
    float distortedX = clamp(texX + distortion.x, 0.001, 0.999);
    float distortedY = clamp(texY + distortion.y, 0.001, 0.999);

    float depth = parseDepth(texture(depthMap, vec2(texX, texY)).r) - parseDepth(gl_FragCoord.z);
    depth = clamp(depth/7, 0.0, 1.0);

    vec3 normCol = texture(normMap, biasedCoord).rgb;
    vec3 norm = vec3(normCol.r*2-1, normCol.b, normCol.g*2-1);
    vec3 unitNorm = normalize(norm);
    vec3 unitLight = normalize(toLightVec);
    vec3 unitCamera = normalize(toCameraVec);

    vec4 reflectionCol = texture(reflection, vec2(distortedX, -distortedY));
    vec4 refractionCol = texture(refraction, vec2(distortedX, distortedY));
    float refractionFac = dot(vec3(0.0, 1.0, 0.0), unitCamera);
    pixel = mix(reflectionCol, refractionCol, refractionFac);
    pixel = mix(pixel, vec4(0.0, 0.3, 0.5, 1.0), 0.2);

    float brightness = max(dot(unitNorm, unitLight), 0.2);
    vec3 diffuse = brightness * lightCol;

    vec3 reflectDir = reflect(-unitLight, unitNorm);
    vec3 specular = pow(max(dot(reflectDir, unitCamera), 0.0), SHINE_DAMPER) * REFLECTIVITY * lightCol;
    pixel = vec4(diffuse, 1.0) * pixel + vec4(specular, 1.0) * depth;

    float dis = length(toCameraVec.xyz);
    float visibility = exp(-pow(dis*FOG_DENSITY, FOG_GRADIENT));
    visibility = clamp(visibility, 0.0, 1.0);
    pixel = mix(vec4(skyCol, 1.0), pixel, visibility);

    pixel.a = depth;
}
