#ifndef _PLAIN_TEXTURE_H
#define _PLAIN_TEXTURE_H

#include <string>
#include "../../../glew.h"

using namespace std;

class PlainTexture
{
public:

    // Constructor
    PlainTexture(const char* _name, GLuint id);

    // Destructor
    ~PlainTexture();

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
