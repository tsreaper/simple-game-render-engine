#ifndef _CUBE_MAP_TEXTURE_H
#define _CUBE_MAP_TEXTURE_H

#include <string>
#include "../../../glew.h"

using namespace std;

class CubeMapTexture
{
public:

    // Constructor
    CubeMapTexture(const char* _name, GLuint _id);

    // Destructor
    ~CubeMapTexture();

    // Get texture name
    const char* getName() const;

    // Get texture id
    GLuint getId() const;

private:

    // Texture name
    string name;

    // Texture id
    GLuint textureId;
};

#endif
