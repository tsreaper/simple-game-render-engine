#ifndef _WATER_FBO_H
#define _WATER_FBO_H

#include "glew.h"
#include "render/object/fbo/fbo.h"

// FBO of water. Used for texturing water
class WaterFbo : public Fbo
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
    GLuint getReflectionTex() const;

    // Get the id of refraction texture
    GLuint getRefractionTex() const;

    // Get the id of refraction depth texture
    GLuint getRefractionDepth() const;

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
    void bindFbo(GLuint fbo, int width, int height);
};

#endif
