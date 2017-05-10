#ifndef WATER_FBO_
#define WATER_FBO_

#include "../../glew.h"

// FBO of water. Used for texturing water
class WaterFbo
{
public:
    
    // Size of reflection FBO
    static const int REFLECTION_WIDTH, REFLECTION_HEIGHT;
    
    // Size of refraction FBO
    static const int REFRACTION_WIDTH, REFRACTION_HEIGHT;
    
    // Constructor
    WaterFbo();
    
    // Destructor
    ~WaterFbo();
    
    // Call before rendering to reflection FBO
    void bindReflectionFbo();
    
    // Call before rendering to refraction FBO
    void bindRefractionFbo();
    
    // Call before rendering back to the default FBO
    void unbindFbo();
    
    // Get the id of reflection texture
    int getReflectionTex() const;
    
    // Get the id of refraction texture
    int getRefractionTex() const;
    
    // Get the id of refraction depth texture
    int getRefractionDepth() const;
    
private:
    
    // Reflection FBO
    GLuint reflectionFbo, reflectionTex, reflectionDepth;
    
    // Refraction FBO
    GLuint refractionFbo, refractionTex, refractionDepth;
    
    // Initialize reflection FBO
    void initReflectionFbo();
    
    // Initialize refraction FBO
    void initRefractionFbo();
    
    // Bind current FBO to render
    void bindFbo(int fbo, int width, int height);
    
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
