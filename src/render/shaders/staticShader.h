#ifndef STATIC_SHADER_H_
#define STATIC_SHADER_H_

#include "basicShader.h"

// Shader for static model
class StaticShader : public BasicShader
{
public:
    
    // Constructor
    StaticShader();
    
    // Vertex shader file name
    static const char* VERTEX_FILE;
    
    // Fragment shader file name
    static const char* FRAGMENT_FILE;
    
    // Load texture property into shader program
    void loadTexture(float reflectivity, float shineDamper);
    
protected:
    
    // Get all uniform locations
    void getAllUniformLocs();
    
private:
    
    // Location of texture reflectivity in shader program
    int reflectivityLoc;
    
    // Location of shine damper in shader program
    int shineDamperLoc;
};

#endif
