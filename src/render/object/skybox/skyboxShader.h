#ifndef _SKYBOX_SHADER_H
#define _SKYBOX_SHADER_H

#include "render/object/shader/basicShader.h"

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
