#ifndef RENDERER_H_
#define RENDERER_H_

#include "../../glew.h"
#include "../entities/entity.h"
#include "../entities/light.h"
#include "../shaders/staticShader.h"

// Model renderer
class Renderer
{
public:
    
    // Clear screen and prepare to render
    static void prepare();
    
    // Render an entity
    static void render(const Entity* entity, StaticShader* shader);
    
    // Bind a textured model
    static void bindTexturedModel(const TexturedModel* model, StaticShader* shader);
    
    // Unbind a textured model
    static void unbindTexturedModel();

private:
    
    // Field of view angle
    static const float FOV;
    
    // Near projection plane
    static const float Z_NEAR;
    
    // Far projection plane
    static const float Z_FAR;
};

#endif
