#include "../../engine/windowManager.h"
#include "waterFbo.h"

// Size of reflection FBO
const int WaterFbo::REFLECTION_WIDTH = 1280;
const int WaterFbo::REFLECTION_HEIGHT = 720;

// Size of refraction FBO
const int WaterFbo::REFRACTION_WIDTH = 1280;
const int WaterFbo::REFRACTION_HEIGHT = 720;

// Constructor
WaterFbo::WaterFbo()
{
    initReflectionFbo();
    initRefractionFbo();
}

// Destructor
WaterFbo::~WaterFbo()
{
    glDeleteFramebuffers(1, &reflectionFbo);
    glDeleteTextures(1, &reflectionTex);
    glDeleteRenderbuffers(1, &reflectionDepth);
    glDeleteFramebuffers(1, &refractionFbo);
    glDeleteTextures(1, &refractionTex);
    glDeleteTextures(1, &refractionDepth);
}

// Call before rendering to reflection FBO
void WaterFbo::bindReflectionFbo()
{
    bindFbo(reflectionFbo, REFLECTION_WIDTH, REFLECTION_HEIGHT);
}

// Call before rendering to refraction FBO
void WaterFbo::bindRefractionFbo()
{
    bindFbo(refractionFbo, REFRACTION_WIDTH, REFRACTION_HEIGHT);
}

// Call before rendering back to the default FBO
void WaterFbo::unbindFbo()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, WindowManager::WINDOW_WIDTH, WindowManager::WINDOW_HEIGHT);
}

// Get the id of reflection texture
GLuint WaterFbo::getReflectionTex() const
{
    return reflectionTex;
}

// Get the id of refraction texture
GLuint WaterFbo::getRefractionTex() const
{
    return refractionTex;
}

// Get the id of refraction depth texture
GLuint WaterFbo::getRefractionDepth() const
{
    return refractionDepth;
}

// Initialize reflection FBO
void WaterFbo::initReflectionFbo()
{
    reflectionFbo = createFbo();
    reflectionTex = createTexAttachment(REFLECTION_WIDTH, REFLECTION_HEIGHT);
    reflectionDepth = createDepthBufferAttachment(REFLECTION_WIDTH, REFLECTION_HEIGHT);
    unbindFbo();
}

// Initialize refraction FBO
void WaterFbo::initRefractionFbo()
{
    refractionFbo = createFbo();
    refractionTex = createTexAttachment(REFRACTION_WIDTH, REFRACTION_HEIGHT);
    refractionDepth = createDepthTexAttachment(REFRACTION_WIDTH, REFRACTION_HEIGHT);
    unbindFbo();
}

// Bind current FBO to render
void WaterFbo::bindFbo(GLuint fbo, int width, int height)
{
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glViewport(0, 0, width, height);
}

// Create a new FBO
GLuint WaterFbo::createFbo()
{
    GLuint fboId[1];
    glGenFramebuffers(1, fboId);
    glBindFramebuffer(GL_FRAMEBUFFER, fboId[0]);
    glDrawBuffer(GL_COLOR_ATTACHMENT0);
    return fboId[0];
}

// Create texture attachment of FBO
GLuint WaterFbo::createTexAttachment(int width, int height)
{
    GLuint texId[1];
    glGenTextures(1, texId);
    glBindTexture(GL_TEXTURE_2D, texId[0]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texId[0], 0);
    return texId[0];
}

// Create depth texture attachment of FBO
GLuint WaterFbo::createDepthTexAttachment(int width, int height)
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
GLuint WaterFbo::createDepthBufferAttachment(int width, int height)
{
    GLuint bufferId[1];
    glGenRenderbuffers(1, bufferId);
    glBindRenderbuffer(GL_RENDERBUFFER, bufferId[0]);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, bufferId[0]);
    return bufferId[0];
}
