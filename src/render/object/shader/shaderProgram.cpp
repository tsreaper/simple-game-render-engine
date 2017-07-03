#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>

#include "render/object/shader/shaderProgram.h"

using namespace std;

// Constructor
ShaderProgram::ShaderProgram(const char* vertexFile, const char* fragmentFile)
{
    vertexShaderId = ShaderProgram::loadShader(vertexFile, GL_VERTEX_SHADER);
    fragmentShaderId = ShaderProgram::loadShader(fragmentFile, GL_FRAGMENT_SHADER);
    programId = glCreateProgram();
    glAttachShader(programId, vertexShaderId);
    glAttachShader(programId, fragmentShaderId);
}

// Destructor
ShaderProgram::~ShaderProgram()
{
    stop();
    glDetachShader(programId, vertexShaderId);
    glDetachShader(programId, fragmentShaderId);
    glDeleteShader(vertexShaderId);
    glDeleteShader(fragmentShaderId);
    glDeleteProgram(programId);
}

// Start shader program
void ShaderProgram::start()
{
    glUseProgram(programId);
}

// Stop shader program
void ShaderProgram::stop()
{
    glUseProgram(0);
}

GLuint ShaderProgram::getUniformLoc(const char* uniName)
{
    return glGetUniformLocation(programId, uniName);
}

// Bind VAO attribute id to shader variable name
void ShaderProgram::bindAttribute(GLuint attr, const char* varName)
{
    glBindAttribLocation(programId, attr, varName);
}

// Load float into uniform by location
void ShaderProgram::loadFloat(GLuint loc, float value)
{
    glUniform1f(loc, value);
}

// Load int into uniform by location
void ShaderProgram::loadInt(GLuint loc, int value)
{
    glUniform1i(loc, value);
}

// Load boolean into uniform by location
void ShaderProgram::loadBool(GLuint loc, bool value)
{
    glUniform1f(loc, value ? 1.0 : 0.0);
}

// Load 3D vector into uniform by location
void ShaderProgram::loadVector3(GLuint loc, vec3 vec)
{
    glUniform3f(loc, vec.x, vec.y, vec.z);
}

// Load 4x4 matrix into uniform by location
void ShaderProgram::loadMatrix4(GLuint loc, const float *value)
{
    glUniformMatrix4fv(loc, 1, GL_FALSE, value);
}

// Load shader from file and compile
GLuint ShaderProgram::loadShader(const char* filename, int type)
{
    // Load shader from file
    ifstream file(filename);

    if (!file.is_open())
    {
        cerr << "ERROR: [ShaderProgram::loadShader] Cannot load shader source " << filename << "!" << endl;
        exit(-1);
    }

    string shaderSource = "";
    string t;
    while (getline(file, t))
        shaderSource += t + "\n";

    // Compile shader
    GLuint shaderId = glCreateShader(type);
    const char* shaderSourceAddr = shaderSource.c_str();
    glShaderSource(shaderId, 1, &shaderSourceAddr, NULL);
    glCompileShader(shaderId);

    // Check compile status
    GLint status[1];
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, status);
    if (status[0] == GL_FALSE)
    {
        GLint logLength[1];
        glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, logLength);
        char* shaderInfo = new char[logLength[0] + 1];
        glGetShaderInfoLog(shaderId, logLength[0], NULL, shaderInfo);

        cerr << "ERROR: [ShaderProgram::loadShader] Cannot compile shader " << filename << "!" << endl;
        cerr << shaderInfo << endl;

        delete[] shaderInfo;
        glDeleteShader(shaderId);
        exit(-1);
    }

    return shaderId;
}
