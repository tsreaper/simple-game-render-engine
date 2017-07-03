#include <cstddef>
#include "render/object/fbo/fbo.h"

// Destructor
Fbo::~Fbo() {}

// Create a new FBO
GLuint Fbo::createFbo()
{
    GLuint fboId[1];
    glGenFramebuffers(1, fboId);
    glBindFramebuffer(GL_FRAMEBUFFER, fboId[0]);
    glDrawBuffer(GL_COLOR_ATTACHMENT0);
    return fboId[0];
}

// Create texture attachment of FBO
GLuint Fbo::createTexAttachment(int width, int height)
{
    GLuint texId[1];
    glGenTextures(1, texId);
    glBindTexture(GL_TEXTURE_2D, texId[0]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texId[0], 0);
    return texId[0];
}

// Create depth texture attachment of FBO
GLuint Fbo::createDepthTexAttachment(int width, int height)
{
    GLuint texId[1];
    glGenTextures(1, texId);
    glBindTexture(GL_TEXTURE_2D, texId[0]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, texId[0], 0);
    return texId[0];
}

// Create depth buffer attachment of FBO
GLuint Fbo::createDepthBufferAttachment(int width, int height)
{
    GLuint bufferId[1];
    glGenRenderbuffers(1, bufferId);
    glBindRenderbuffer(GL_RENDERBUFFER, bufferId[0]);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, bufferId[0]);
    return bufferId[0];
}
