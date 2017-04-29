#include "../../glew.h"
#include "staticShader.h"

// Vertex shader file name
const char* StaticShader::VERTEX_FILE = "src/render/shaders/shaderSource/vertexShader.glsl";

// Static shader file name
const char* StaticShader::FRAGMENT_FILE = "src/render/shaders/shaderSource/fragmentShader.glsl";

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

// Load light position into shader program
void StaticShader::loadLightPos(float x, float y, float z)
{
    loadVector3(lightPosLoc, x, y, z);
}

// Load light color into shader program
void StaticShader::loadLightCol(float r, float g, float b)
{
    loadVector3(lightColLoc, r, g, b);
}

// Load texture reflectivity into shader program
void StaticShader::loadReflectivity(float reflectivity)
{
    loadFloat(reflectivityLoc, reflectivity);
}

// Load texture shine damper into shader program
void StaticShader::loadShineDamper(float shineDamper)
{
    loadFloat(shineDamperLoc, shineDamper);
}

// Get all uniform locations
void StaticShader::getAllUniformLocs()
{
    transMatrixLoc = getUniformLoc("transMatrix");
    cameraMatrixLoc = getUniformLoc("cameraMatrix");
    projMatrixLoc = getUniformLoc("projMatrix");
    lightPosLoc = getUniformLoc("lightPos");
    lightColLoc = getUniformLoc("lightCol");
    reflectivityLoc = getUniformLoc("reflectivity");
    shineDamperLoc = getUniformLoc("shineDamper");
}

// Bind VAO attributes
void StaticShader::bindAttributes()
{
    // Bind vertex position and texture coordinate
    bindAttribute(0, "position");
    bindAttribute(1, "textureCoord");
    bindAttribute(2, "norm");
}
