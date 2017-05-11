#include "waterShader.h"

// Vertex shader file name
const char* WaterShader::VERTEX_FILE = "src/render/shaders/shaderSource/waterVertexShader.glsl";

// Fragment shader file name
const char* WaterShader::FRAGMENT_FILE = "src/render/shaders/shaderSource/waterFragmentShader.glsl";

// Constructor
WaterShader::WaterShader(): BasicShader(VERTEX_FILE, FRAGMENT_FILE, 0)
{
    getAllUniformLocs();
    
    start();
    connectTextures();
    stop();
}

// Load DUDV map moving factor into shader program
void WaterShader::loadMoveFac(float moveFac)
{
    loadFloat(moveFacLoc, moveFac);
}

// Get all uniform locations
void WaterShader::getAllUniformLocs()
{
    reflectionLoc = getUniformLoc("reflection");
    refractionLoc = getUniformLoc("refraction");
    dudvMapLoc = getUniformLoc("dudvMap");
    moveFacLoc = getUniformLoc("moveFac");
}

// Connect texture units to shader program
void WaterShader::connectTextures()
{
    loadInt(reflectionLoc, 0);
    loadInt(refractionLoc, 1);
    loadInt(dudvMapLoc, 2);
}
