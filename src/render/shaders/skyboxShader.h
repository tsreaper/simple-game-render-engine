#ifndef SKYBOX_SHADER_H_
#define SKYBOX_SHADER_H_

#include "../../glew.h"
#include "shaderProgram.h"

// Shader for skybox
class SkyboxShader : public ShaderProgram
{
public:
    
    // Vertex shader file name
    static const char* VERTEX_FILE;

    // Fragment shader file name
    static const char* FRAGMENT_FILE;
    
    // Constructor
    SkyboxShader();
    
    // Load transformation matrix into shader program
    void loadTransMatrix(const float* matrix);
    
    // Load camera matrix into shader program
    void loadCameraMatrix(const float* matrix);
    
    // Load projection matrix into shader program
    void loadProjMatrix(const float* matrix);
    
    // Load sky color into shader program
    void loadSkyCol(float r, float g, float b);
    
private:
    
    // Get all uniform locations
    void getAllUniformLocs();
    
    // Bind VAO attributes
    void bindAttributes();
    
    // Location of transformation matrix in shader program
    int transMatrixLoc;
    
    // Location of camera matrix in the shader program
    int cameraMatrixLoc;
    
    // Location of projection matrix in shader program
    int projMatrixLoc;
    
    // Location of sky color in shader program
    int skyColLoc;
};

#endif
