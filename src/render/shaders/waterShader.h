#ifndef WATER_SHADER_H_
#define WATER_SHADER_H_

#include "basicShader.h"

// Shader for water
class WaterShader : public BasicShader
{
public:
    
    // Constructor
    WaterShader();
    
    // Vertex shader file name
    static const char* VERTEX_FILE;
    
    // Fragment shader file name
    static const char* FRAGMENT_FILE;
    
    // Load DUDV map moving factor into shader program
    void loadMoveFac(float moveFac);
    
protected:
    
    // Get all uniform locations
    void getAllUniformLocs();
    
private:
    
    // Location of reflection texture in the shader program
    int reflectionLoc;
    
    // Location of refraction texture in the shader program
    int refractionLoc;
    
    // Location of DUDV map in the shader program
    int dudvMapLoc;
    
    // Location of DUDV map moving factor in the shader program
    float moveFacLoc;
    
    // Connect texture units to shader program
    void connectTextures();
};

#endif
