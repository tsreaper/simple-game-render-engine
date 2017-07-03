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

    // Load night factor into shader program
    void loadNightFac(float nightFac);

protected:

    // Get all uniform locations
    void getAllUniformLocs() override;

private:

    // Locations of day/night textures in shader program
    GLuint dayLoc, nightLoc;

    // Location of night factor in shader program
    GLuint nightFacLoc;

    // Connect texture units to shader program
    void connectTextures();
    
};

#endif
