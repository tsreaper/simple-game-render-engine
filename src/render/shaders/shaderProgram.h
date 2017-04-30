#ifndef STATIC_PROGRAM_H_
#define STATIC_PROGRAM_H_

#include "../../glew.h"

// Base class for shader
class ShaderProgram
{
public:
    
    // Constructor
    ShaderProgram(const char* vertexFile, const char* fragmentFile);
    
    // Start shader program
    void start();
    
    // Stop shader program
    void stop();
    
    // Clean up shaders
    void cleanUp();
    
protected:
    
    // Shader program id
    int programId;
    
    // Interface. Get all uniform locations
    virtual void getAllUniformLocs() = 0;
    
    // Get uniform location in the shader program by name
    getUniformLoc(const char* uniName);
    
    // Interface. Bind VAO attributes
    virtual void bindAttributes() = 0;
    
    // Bind VAO attribute id to shader variable name
    void bindAttribute(int attr, const char* varName);
    
    // Load float into uniform by location
    void loadFloat(int loc, float value);
    
    // Load boolean into uniform by location
    void loadBool(int loc, bool value);
    
    // Load 3D vector into uniform by location
    void loadVector3(int loc, float x, float y, float z);
    
    // Load 4x4 matrix into uniform by location
    void loadMatrix4(int loc, const float *value);
    
private:
    
    // Vertex shader id
    int vertexShaderId;
    
    // Fragment shader id
    int fragmentShaderId;
    
    // Load shader from file and compile
    static int loadShader(const char* filename, int type);
};

#endif
