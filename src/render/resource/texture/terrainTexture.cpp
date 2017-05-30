#include "terrainTexture.h"

// Constructor
TerrainTexture::TerrainTexture(
    const char* _name, GLuint _k, GLuint _r, GLuint _g, GLuint _b, GLuint _blend
): name(_name), k(_k), r(_r), g(_g), b(_b), blend(_blend) {}

// Destructor
TerrainTexture::~TerrainTexture()
{
    glDeleteTextures(1, &k);
    glDeleteTextures(1, &r);
    glDeleteTextures(1, &g);
    glDeleteTextures(1, &b);
    glDeleteTextures(1, &blend);
}

// Get name of texture pack
const char* TerrainTexture::getName() const
{
    return name.c_str();
}

// Get black texture
GLuint TerrainTexture::getK() const
{
    return k;
}

// Get red texture
GLuint TerrainTexture::getR() const
{
    return r;
}

// Get green texture
GLuint TerrainTexture::getG() const
{
    return g;
}

// Get blue texture
GLuint TerrainTexture::getB() const
{
    return b;
}

// Get blend map
GLuint TerrainTexture::getBlend() const
{
    return blend;
}
