#ifndef _FBO_H
#define _FBO_H

#include "glew.h"

// Basic FBO
class Fbo
{
public:

    // Destructor
    virtual ~Fbo();

protected:

    // Create a new FBO
    GLuint createFbo();

    // Create texture attachment of FBO
    GLuint createTexAttachment(int width, int height);

    // Create depth texture attachment of FBO
    GLuint createDepthTexAttachment(int width, int height);

    // Create depth buffer attachment of FBO
    GLuint createDepthBufferAttachment(int width, int height);
};

#endif
