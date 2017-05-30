#ifndef _SHADER_PROGRAM_H
#define _SHADER_PROGRAM_H

#include "../../../glew.h"

// Base class for shader
class ShaderProgram
{
public:

    // Constructor
    ShaderProgram(const char* vertexFile, const char* fragmentFile);

    // Destructor
    virtual ~ShaderProgram();

    // Start shader program
    void start();

    // Stop shader program
    void stop();

protected:

    // Shader program id
    GLuint programId;

    // Interface. Get all uniform locations
    virtual void getAllUniformLocs() = 0;

    // Get uniform location in the shader program by name
    GLuint getUniformLoc(const char* uniName);

    // Interface. Bind VAO attributes
    virtual void bindAttributes() = 0;

    // Bind VAO attribute id to shader variable name
    void bindAttribute(GLuint attr, const char* varName);

    // Load float into uniform by location
    void loadFloat(GLuint loc, float value);

    // Load int into uniform by location
    void loadInt(GLuint loc, int value);

    // Load boolean into uniform by location
    void loadBool(GLuint loc, bool value);

    // Load 3D vector into uniform by location
    void loadVector3(GLuint loc, float x, float y, float z);

    // Load 4x4 matrix into uniform by location
    void loadMatrix4(GLuint loc, const float *value);

private:

    // Vertex shader id
    GLuint vertexShaderId;

    // Fragment shader id
    GLuint fragmentShaderId;

    // Load shader from file and compile
    static GLuint loadShader(const char* filename, int type);
};

#endif
