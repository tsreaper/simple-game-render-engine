#include "skyboxShader.h"

// Vertex shader file name
const char* SkyboxShader::VERTEX_FILE = "src/render/shaders/shaderSource/skyboxVertexShader.glsl";

// Fragment shader file name
const char* SkyboxShader::FRAGMENT_FILE = "src/render/shaders/shaderSource/skyboxFragmentShader.glsl";

// Constructor
SkyboxShader::SkyboxShader(): BasicShader(VERTEX_FILE, FRAGMENT_FILE, SHADER_LOAD_CLIP) {}
