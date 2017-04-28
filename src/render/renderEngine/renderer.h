#ifndef RENDERER_H_
#define RENDERER_H_

#include "../entities/entity.h"
#include "../shaders/staticShader.h"

// Model renderer
class Renderer
{
public:
    
    // Clear screen and prepare to render
    static void prepare();
    
    // Render a model
    static void render(const Entity* entity);
    
    // Set current shader
    static void setShader(StaticShader* _shader);

private:
    
    // Field of view angle
    static const float FOV;
    
    // Near projection plane
    static const float Z_NEAR;
    
    // Far projection plane
    static const float Z_FAR;
    
    // Shader program used for rendering
    static StaticShader* shader;
};

#endif
