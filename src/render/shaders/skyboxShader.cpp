#include "skyboxShader.h"

// Vertex shader file name
const char* SkyboxShader::VERTEX_FILE = "src/render/shaders/shaderSource/skyboxVertexShader.glsl";

// Fragment shader file name
const char* SkyboxShader::FRAGMENT_FILE = "src/render/shaders/shaderSource/skyboxFragmentShader.glsl";

// Constructor
SkyboxShader::SkyboxShader(): ShaderProgram(VERTEX_FILE, FRAGMENT_FILE)
{
    // Bind VAO attributes and link program
    bindAttributes();
    glLinkProgram(programId);
    glValidateProgram(programId);
    getAllUniformLocs();
}

// Load transformation matrix into shader program
void SkyboxShader::loadTransMatrix(const float* matrix)
{
    loadMatrix4(transMatrixLoc, matrix);
}

// Load camera matrix into shader program
void SkyboxShader::loadCameraMatrix(const float* matrix)
{
    loadMatrix4(cameraMatrixLoc, matrix);
}

// Load projection matrix into shader program
void SkyboxShader::loadProjMatrix(const float* matrix)
{
    loadMatrix4(projMatrixLoc, matrix);
}

// Load sky color into shader program
void SkyboxShader::loadSkyCol(float r, float g, float b)
{
    loadVector3(skyColLoc, r, g, b);
}

// Get all uniform locations
void SkyboxShader::getAllUniformLocs()
{
    transMatrixLoc = getUniformLoc("transMatrix");
    cameraMatrixLoc = getUniformLoc("cameraMatrix");
    projMatrixLoc = getUniformLoc("projMatrix");
    skyColLoc = getUniformLoc("skyCol");
}

// Bind VAO attributes
void SkyboxShader::bindAttributes()
{
    // Bind vertex position only
    bindAttribute(0, "position");
}
