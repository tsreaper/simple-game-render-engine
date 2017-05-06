#ifndef BASIC_SHADER_H_
#define BASIC_SHADER_H_

#include "../../glew.h"
#include "shaderProgram.h"

// Shader for static model
class BasicShader : public ShaderProgram
{
public:
    
    // Constructor
    BasicShader(const char* vertexFile, const char* fragmentFile);
    
    // Load transformation matrix into shader program
    void loadTransMatrix(const float* matrix);
    
    // Load camera matrix into shader program
    void loadCameraMatrix(const float* matrix);
    
    // Load projection matrix into shader program
    void loadProjMatrix(const float* matrix);
    
    // Load light into shader program
    void loadLight(float x, float y, float z, float r, float g, float b);
    
    // Load sky color into shader program
    void loadSkyCol(float r, float g, float b);
    
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
    
    // Location of light position in shader program
    int lightPosLoc;
    
    // Location of light color in shader program
    int lightColLoc;
    
    // Location of sky color in shader program
    int skyColLoc;
};

#endif
