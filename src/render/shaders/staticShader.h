#ifndef STATIC_SHADER_H_
#define STATIC_SHADER_H_

#include "shaderProgram.h"

// Shader for static model
class StaticShader : public ShaderProgram
{
public:
    
    // Constructor
    StaticShader();
    
    // Vertex shader file name
    static const char* VERTEX_FILE;
    
    // Fragment shader file name
    static const char* FRAGMENT_FILE;
    
    // Load transformation matrix into shader program
    void loadTransMatrix(const float* matrix);
    
    // Load camera matrix into shader program
    void loadCameraMatrix(const float* matrix);
    
    // Load projection matrix into shader program
    void loadProjMatrix(const float* matrix);
    
protected:
    
    // Get all uniform locations
    void getAllUniformLocs() override;
    
    // Bind VAO attributes
    void bindAttributes() override;
    
private:
    
    // Location of transformation matrix in shader program
    int transMatrixLoc;
    
    // Location of camera matrix in the shader program
    int cameraMatrixLoc;
    
    // Location of projection matrix in shader program
    int projMatrixLoc;
};

#endif