#version 400 core

in vec4 passCoord;
in vec2 texCoord;
in vec3 toCameraVec;
in vec3 toLightVec[8];

out vec4 pixel;

uniform sampler2D reflection;
uniform sampler2D refraction;
uniform sampler2D dudvMap;
uniform sampler2D normMap;
uniform sampler2D depthMap;
uniform float moveFac;

uniform vec3 lightCol[8];
uniform vec3 lightAttenuation[8];

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

float calcAttenuation(vec3 fac, float dis)
{
    return fac.x + fac.y * dis + fac.z * dis * dis;
}

void main(void)
{
    // Calculate water distortion
    vec2 biasedCoord = texture(dudvMap, vec2(texCoord.x + moveFac, texCoord.y)).rg * 0.1;
    biasedCoord = texCoord + vec2(biasedCoord.x ,biasedCoord.y + moveFac);
    vec2 distortion = (texture(dudvMap, biasedCoord).rg*2-1) * WAVE_STRENGTH;
    // vec2 distortion = vec2(0, 0);
    float texX = passCoord.x/passCoord.w/2+0.5;
    float texY = passCoord.y/passCoord.w/2+0.5;
    float distortedX = clamp(texX + distortion.x, 0.001, 0.999);
    float distortedY = clamp(texY + distortion.y, 0.001, 0.999);

    // Water depth effect. Shallow water will be more transparent and less reflective
    float depth = parseDepth(texture(depthMap, vec2(texX, texY)).r) - parseDepth(gl_FragCoord.z);
    depth = clamp(depth/10, 0.0, 1.0);

    // Calculate light
    vec3 normCol = texture(normMap, biasedCoord).rgb;
    vec3 norm = vec3(normCol.r*2-1, normCol.b*1.5, normCol.g*2-1);
    vec3 unitNorm = normalize(norm);
    vec3 unitCamera = normalize(toCameraVec);

    vec4 reflectionCol = texture(reflection, vec2(distortedX, -distortedY));
    vec4 refractionCol = texture(refraction, vec2(distortedX, distortedY));
    float refractionFac = dot(vec3(0.0, 1.0, 0.0), unitCamera);
    pixel = mix(reflectionCol, refractionCol, refractionFac);
    pixel = mix(pixel, vec4(0.0, 0.3, 0.5, 1.0), 0.2);

    vec3 unitLight[8];
    for (int i = 0; i < 8; i++)
        unitLight[i] = normalize(toLightVec[i]);

    vec3 diffuse = vec3(0, 0, 0);
    vec3 specular = vec3(0, 0, 0);
    for (int i = 0; i < 8; i++)
    {
        float dis = length(toLightVec[i]);
        float attenuation = calcAttenuation(lightAttenuation[i], dis);
        diffuse += dot(unitNorm, unitLight[i])/attenuation * lightCol[i];

        vec3 reflectDir = reflect(-unitLight[i], unitNorm);
        specular += pow(max(dot(reflectDir, unitCamera)/attenuation, 0.0), SHINE_DAMPER) * REFLECTIVITY * lightCol[i];
    }
    diffuse = max(diffuse, 0.2);

    pixel = vec4(diffuse, 1.0) * pixel + vec4(specular, 1.0) * depth;

    // Calculate fog
    float dis = length(toCameraVec.xyz);
    float visibility = exp(-pow(dis*FOG_DENSITY, FOG_GRADIENT));
    visibility = clamp(visibility, 0.0, 1.0);
    pixel = mix(vec4(skyCol, 1.0), pixel, visibility);

    pixel.a = depth;
}
