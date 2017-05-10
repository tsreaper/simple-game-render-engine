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
};

#endif
