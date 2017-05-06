#ifndef TERRAIN_SHADER_H_
#define TERRAIN_SHADER_H_

#include "basicShader.h"

// Shader for terrain
class TerrainShader : public BasicShader
{
public:
    
    // Constructor
    TerrainShader();
    
    // Vertex shader file name
    static const char* VERTEX_FILE;
    
    // Fragment shader file name
    static const char* FRAGMENT_FILE;
    
protected:
    
    // Get all uniform locations
    void getAllUniformLocs();
    
private:
    
    // Locations of RGBK textures in the shader program
    int kLoc, rLoc, gLoc, bLoc;
    
    // Location of blend map in the shader program
    int blendLoc;
    
    // Connect texture units to shader program
    void connectTextures();
};

#endif
