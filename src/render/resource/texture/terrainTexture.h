#ifndef _TERRAIN_TEXTURE_H
#define _TERRAIN_TEXTURE_H

#include <string>
#include "glew.h"

using namespace std;

// Terrain multi-texture
class TerrainTexture
{
public:

    // Constructor
    TerrainTexture(const char* _name, GLuint _k, GLuint _r, GLuint _g, GLuint _b, GLuint _blend);

    // Destructor
    ~TerrainTexture();

    // Get name of texture pack
    const char* getName() const;

    // Get black texture
    GLuint getK() const;

    // Get red texture
    GLuint getR() const;

    // Get green texture
    GLuint getG() const;

    // Get blue texture
    GLuint getB() const;

    // Get blend map
    GLuint getBlend() const;

private:

    // Name of texture pack
    string name;

    // Textures
    GLuint k, r, g, b;

    // Blend map
    GLuint blend;
};

#endif
