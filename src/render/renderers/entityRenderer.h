#ifndef ENTITY_RENDERER_H_
#define ENTITY_RENDERER_H_

#include "../../glew.h"
#include "../entities/entity.h"
#include "../shaders/staticShader.h"

// Entity renderer
class EntityRenderer
{
public:
    
    // Render an entity
    static void render(const Entity* entity, StaticShader* shader);
    
    // Bind a textured model
    static void bindTexturedModel(const TexturedModel* model, StaticShader* shader);
    
    // Unbind a textured model
    static void unbindTexturedModel();
};

#endif
