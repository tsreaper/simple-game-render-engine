#ifndef STATIC_SHADER_H_
#define STATIC_SHADER_H_

#include "shaderProgram.h"

class StaticShader : public ShaderProgram
{
    public:
    
    StaticShader();
    
    static char* VERTEX_FILE;
    static char* FRAGMENT_FILE;
    
    protected:
    
    void bindAttributes();
};

#endif
