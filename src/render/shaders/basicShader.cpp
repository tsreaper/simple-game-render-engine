#include "basicShader.h"

// Constructor
BasicShader::BasicShader(const char* vertexFile, const char* fragmentFile): ShaderProgram(vertexFile, fragmentFile)
{
    // Bind VAO attributes and link program
    bindAttributes();
    glLinkProgram(programId);
    glValidateProgram(programId);
    getAllUniformLocs();
}

// Load transformation matrix into shader program
void BasicShader::loadTransMatrix(const float* matrix)
{
    loadMatrix4(transMatrixLoc, matrix);
}

// Load camera matrix into shader program
void BasicShader::loadCameraMatrix(const float* matrix)
{
    loadMatrix4(cameraMatrixLoc, matrix);
}

// Load projection matrix into shader program
void BasicShader::loadProjMatrix(const float* matrix)
{
    loadMatrix4(projMatrixLoc, matrix);
}

// Load light into shader program
void BasicShader::loadLight(float x, float y, float z, float r, float g, float b)
{
    loadVector3(lightPosLoc, x, y, z);
    loadVector3(lightColLoc, r, g, b);
}

// Load sky color into shader program
void BasicShader::loadSkyCol(float r, float g, float b)
{
    loadVector3(skyColLoc, r, g, b);
}

// Get all uniform locations
void BasicShader::getAllUniformLocs()
{
    transMatrixLoc = getUniformLoc("transMatrix");
    cameraMatrixLoc = getUniformLoc("cameraMatrix");
    projMatrixLoc = getUniformLoc("projMatrix");
    lightPosLoc = getUniformLoc("lightPos");
    lightColLoc = getUniformLoc("lightCol");
    skyColLoc = getUniformLoc("skyCol");
}

// Bind VAO attributes
void BasicShader::bindAttributes()
{
    // Bind vertex position and texture coordinate
    bindAttribute(0, "position");
    bindAttribute(1, "textureCoord");
    bindAttribute(2, "norm");
}
