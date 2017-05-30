#ifndef _ENTITY_RENDERER_H
#define _ENTITY_RENDERER_H

#include "../../../glew.h"
#include "entity.h"
#include "entityShader.h"

// Entity renderer
class EntityRenderer
{
public:

    // Render an entity
    void render(const Entity* entity, EntityShader* shader);

    // Bind an entity
    void bindEntity(const Entity* entity, EntityShader* shader);

    // Unbind an entity
    void unbindEntity();
};

#endif
