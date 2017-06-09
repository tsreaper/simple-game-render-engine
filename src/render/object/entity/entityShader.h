#ifndef _ENTITY_SHADER_H
#define _ENTITY_SHADER_H

#include "render/object/shader/basicShader.h"

// Shader for static model
class EntityShader : public BasicShader
{
public:

    // Constructor
    EntityShader();

    // Vertex shader file name
    static const char* VERTEX_FILE;

    // Fragment shader file name
    static const char* FRAGMENT_FILE;

    // Load texture property into shader program
    void loadTexture(float reflectivity, float shineDamper, int atlasRows);

    // Load atlas position into shader program
    void loadAtlasPos(int atlasPos);

protected:

    // Get all uniform locations
    void getAllUniformLocs() override;

private:

    // Location of texture reflectivity in shader program
    GLuint reflectivityLoc;

    // Location of shine damper in shader program
    GLuint shineDamperLoc;

    // Location of atlas information
    GLuint atlasRowsLoc, atlasPosLoc;
};

#endif
