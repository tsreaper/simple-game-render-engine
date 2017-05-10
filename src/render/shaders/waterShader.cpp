#include "waterShader.h"

// Vertex shader file name
const char* WaterShader::VERTEX_FILE = "src/render/shaders/shaderSource/waterVertexShader.glsl";

// Fragment shader file name
const char* WaterShader::FRAGMENT_FILE = "src/render/shaders/shaderSource/waterFragmentShader.glsl";

// Constructor
WaterShader::WaterShader(): BasicShader(VERTEX_FILE, FRAGMENT_FILE)
{
}
