#ifndef SKYBOX_SHADER_H_
#define SKYBOX_SHADER_H_

#include "../../glew.h"
#include "basicShader.h"

// Shader for skybox
class SkyboxShader : public BasicShader
{
public:
    
    // Vertex shader file name
    static const char* VERTEX_FILE;

    // Fragment shader file name
    static const char* FRAGMENT_FILE;
    
    // Constructor
    SkyboxShader();
};

#endif
