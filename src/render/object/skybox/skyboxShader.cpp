#include "render/object/skybox/skyboxShader.h"

// Vertex shader file name
const char* SkyboxShader::VERTEX_FILE = "src/render/object/skybox/skyboxVertex.glsl";

// Fragment shader file name
const char* SkyboxShader::FRAGMENT_FILE = "src/render/object/skybox/skyboxFragment.glsl";

// Constructor
SkyboxShader::SkyboxShader(): BasicShader(VERTEX_FILE, FRAGMENT_FILE, SHADER_LOAD_CLIP)
{
    getAllUniformLocs();

    start();
    connectTextures();
    stop();
}

// Load night factor into shader program
void SkyboxShader::loadNightFac(float nightFac)
{
    loadFloat(nightFacLoc, nightFac);
}

// Get all uniform locations
void SkyboxShader::getAllUniformLocs()
{
    dayLoc = getUniformLoc("textureDay");
    nightLoc = getUniformLoc("textureNight");

    nightFacLoc = getUniformLoc("nightFac");
}

// Connect texture units to shader program
void SkyboxShader::connectTextures()
{
    loadInt(dayLoc, 0);
    loadInt(nightLoc, 1);
}
