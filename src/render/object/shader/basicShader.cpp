#include <string>
#include "render/object/shader/basicShader.h"

using namespace std;

// Shader functions
const int BasicShader::SHADER_LOAD_LIGHT = 1;
const int BasicShader::SHADER_LOAD_CLIP = 2;
const int BasicShader::SHADER_BIND_TEX_NORM = 4;

// Max light rendered
const int BasicShader::MAX_LIGHT_SIZE = 8;

// Constructor
BasicShader::BasicShader(const char* vertexFile, const char* fragmentFile, int _mode): ShaderProgram(vertexFile, fragmentFile)
{
    mode = _mode;
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
void BasicShader::loadLight(Light* light[], int size)
{
    if (mode & SHADER_LOAD_LIGHT)
    {
        int cnt = min(size, MAX_LIGHT_SIZE);
        for (int i = 0; i < cnt; i++)
        {
            loadVector3(lightPosLoc[i], light[i]->getPos());
            loadVector3(lightColLoc[i], light[i]->getCol());
            loadVector3(lightAttenuationLoc[i], light[i]->getAtt());
        }
        for (int i = size; i < MAX_LIGHT_SIZE; i++)
        {
            loadVector3(lightPosLoc[i], vec3(0, 0, 0));
            loadVector3(lightColLoc[i], vec3(0, 0, 0));
            loadVector3(lightAttenuationLoc[i], vec3(1, 0, 0));
        }
    }
}

// Load sky color into shader program
void BasicShader::loadSkyCol(vec3 col)
{
    loadVector3(skyColLoc, col);
}

// Load clipping plane info into shader program
void BasicShader::loadClipping(float height, bool clipPositive)
{
    if (mode & SHADER_LOAD_CLIP)
    {
        loadFloat(clipHeightLoc, height);
        loadBool(clipPositiveLoc, clipPositive);
    }
}

// Get all uniform locations
void BasicShader::getAllUniformLocs()
{
    transMatrixLoc = getUniformLoc("transMatrix");
    cameraMatrixLoc = getUniformLoc("cameraMatrix");
    projMatrixLoc = getUniformLoc("projMatrix");

    if (mode & SHADER_LOAD_LIGHT)
    {
        for (int i = 0; i < MAX_LIGHT_SIZE; i++)
        {
            lightPosLoc[i] = getUniformLoc(("lightPos[" + to_string(i) + "]").c_str());
            lightColLoc[i] = getUniformLoc(("lightCol[" + to_string(i) + "]").c_str());
            lightAttenuationLoc[i] = getUniformLoc(("lightAttenuation[" + to_string(i) + "]").c_str());
        }
    }

    skyColLoc = getUniformLoc("skyCol");

    if (mode & SHADER_LOAD_CLIP)
    {
        clipHeightLoc = getUniformLoc("clipHeight");
        clipPositiveLoc = getUniformLoc("clipPositive");
    }
}

// Bind VAO attributes
void BasicShader::bindAttributes()
{
    // Bind vertex position and texture coordinate
    bindAttribute(0, "position");

    if (SHADER_BIND_TEX_NORM)
    {
        bindAttribute(1, "textureCoord");
        bindAttribute(2, "norm");
    }
}
