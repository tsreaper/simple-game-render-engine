#include "skyboxShader.h"

// Vertex shader file name
const char* SkyboxShader::VERTEX_FILE = "src/render/object/skybox/skyboxVertex.glsl";

// Fragment shader file name
const char* SkyboxShader::FRAGMENT_FILE = "src/render/object/skybox/skyboxFragment.glsl";

// Constructor
SkyboxShader::SkyboxShader(): BasicShader(VERTEX_FILE, FRAGMENT_FILE, SHADER_LOAD_CLIP) {}
