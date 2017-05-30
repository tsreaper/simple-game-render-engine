#ifndef _WATER_SHADER_H
#define _WATER_SHADER_H

#include "../shader/basicShader.h"

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
    GLuint reflectionLoc;

    // Location of refraction texture in the shader program
    GLuint refractionLoc;

    // Location of DUDV map in the shader program
    GLuint dudvMapLoc;

    // Location of normal map in the shader program
    GLuint normMapLoc;

    // Location of depth map in the shader program
    GLuint depthMapLoc;

    // Location of DUDV map moving factor in the shader program
    GLuint moveFacLoc;

    // Connect texture units to shader program
    void connectTextures();
};

#endif
