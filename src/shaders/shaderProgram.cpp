#include <string>
#include <iostream>
#include <fstream>
#include "../glew.h"
#include "shaderProgram.h"

using namespace std;

ShaderProgram::ShaderProgram(char* vertexFile, char* fragmentFile)
{
    vertexShaderId = ShaderProgram::loadShader(vertexFile, GL_VERTEX_SHADER);
    fragmentShaderId = ShaderProgram::loadShader(fragmentFile, GL_FRAGMENT_SHADER);
    programId = glCreateProgram();
    glAttachShader(programId, vertexShaderId);
    glAttachShader(programId, fragmentShaderId);
}

void ShaderProgram::start()
{
    glUseProgram(programId);
}

void ShaderProgram::stop()
{
    glUseProgram(0);
}

void ShaderProgram::cleanUp()
{
    stop();
    glDetachShader(programId, vertexShaderId);
    glDetachShader(programId, fragmentShaderId);
    glDeleteShader(vertexShaderId);
    glDeleteShader(fragmentShaderId);
    glDeleteProgram(programId);
}

void ShaderProgram::bindAttributes() {}

void ShaderProgram::bindAttribute(int attr, char* varName)
{
    glBindAttribLocation(programId, attr, varName);
}

int ShaderProgram::loadShader(char* filename, int type)
{
    ifstream file(filename);
    
    if (!file.is_open())
    {
        cerr << "Can't load file " << filename << "!" << endl;
        return -1;
    }
    
    string shaderSource = "";
    string t;
    while (getline(file, t))
        shaderSource += t + "\n";
    
    GLuint shaderId = glCreateShader(type);
    const char* shaderSourceAddr = shaderSource.c_str();
    glShaderSource(shaderId, 1, &shaderSourceAddr, NULL);
    glCompileShader(shaderId);
    
    GLint status[1];
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, status);
    if (status[0] == GL_FALSE)
    {
        GLint logLength[1];
        glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, logLength);
        char* shaderInfo = new char[logLength[0] + 1];
        glGetShaderInfoLog(shaderId, logLength[0], NULL, shaderInfo);

        cerr << "ERROR: Could not compile shader!" << endl;
        cerr << shaderInfo << endl;

        delete[] shaderInfo;
        glDeleteShader(shaderId);
        return -1;
    }
    
    return shaderId;
}
