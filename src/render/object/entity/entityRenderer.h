#ifndef _ENTITY_RENDERER_H
#define _ENTITY_RENDERER_H

#include "glew.h"

#include "render/object/light/light.h"
#include "render/object/entity/entity.h"
#include "render/object/entity/entityShader.h"

// Entity renderer
class EntityRenderer
{
public:

    // Render an entity
    void render(const Entity* entity, Light* light[], int lightSize, EntityShader* shader);

    // Bind an entity
    void bindEntity(const Entity* entity, EntityShader* shader);

    // Unbind an entity
    void unbindEntity();

private:

    // Sort light
    void sortLight(Light* light[], int lightSize, const Entity* entity);
};

#endif
