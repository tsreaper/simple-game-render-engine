#include "../../glew.h"
#include "staticShader.h"

// Vertex shader file name
const char* StaticShader::VERTEX_FILE = "src/render/shaders/shaderSource/vertexShader.txt";

// Static shader file name
const char* StaticShader::FRAGMENT_FILE = "src/render/shaders/shaderSource/fragmentShader.txt";

// Constructor
StaticShader::StaticShader(): ShaderProgram(VERTEX_FILE, FRAGMENT_FILE)
{
    // Bind VAO attributes and link program
    bindAttributes();
    glLinkProgram(programId);
    glValidateProgram(programId);
    getAllUniformLocs();
}

// Load transformation matrix into shader program
void StaticShader::loadTransMatrix(const float* matrix)
{
    loadMatrix4(transMatrixLoc, matrix);
}

// Load camera matrix into shader program
void StaticShader::loadCameraMatrix(const float* matrix)
{
    loadMatrix4(cameraMatrixLoc, matrix);
}

// Load projection matrix into shader program
void StaticShader::loadProjMatrix(const float* matrix)
{
    loadMatrix4(projMatrixLoc, matrix);
}

// Get all uniform locations
void StaticShader::getAllUniformLocs()
{
    transMatrixLoc = getUniformLoc("transMatrix");
    cameraMatrixLoc = getUniformLoc("cameraMatrix");
    projMatrixLoc = getUniformLoc("projMatrix");
}

// Bind VAO attributes
void StaticShader::bindAttributes()
{
    // Bind vertex position and texture coordinate
    bindAttribute(0, "position");
    bindAttribute(1, "textureCoords");
}
