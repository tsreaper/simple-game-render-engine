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
    
    // Load light position into shader program
    void loadLightPos(float x, float y, float z);
    
    // Load light color into shader program
    void loadLightCol(float r, float g, float b);
    
    // Load texture reflectivity into shader program
    void loadReflectivity(float reflectivity);

    // Load texture shine damper into shader program
    void loadShineDamper(float shineDamper);
    
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
    
    // Location of texture reflectivity in shader program
    float reflectivityLoc;
    
    // Location of shine damper in shader program
    float shineDamperLoc;
};

#endif
