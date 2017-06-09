#include <algorithm>

#include "utils/math/math.h"
#include "render/resource/texture/modelTexture.h"
#include "render/object/entity/entityRenderer.h"

using namespace std;

// Render an entity
void EntityRenderer::render(const Entity* entity, Light* light[], int lightSize, EntityShader* shader)
{
    // Calculate transformation matrix
    float* transMatrix = Math::createTransMatrix(
        entity->getTX(), entity->getTY(), entity->getTZ(),
        entity->getRX(), entity->getRY(), entity->getRZ(),
        entity->getScale()
    );
    shader->loadTransMatrix(transMatrix);

    // Load atlas position
    shader->loadAtlasPos(entity->getAtlasPos());

    // Sort and load light
    sortLight(light, lightSize, entity);
    shader->loadLight(light, lightSize);

    // Draw model
    glDrawElements(GL_TRIANGLES, entity->getModel()->getVertexCount(), GL_UNSIGNED_INT, NULL);

    delete[] transMatrix;
}

// Bind an entity
void EntityRenderer::bindEntity(const Entity* entity, EntityShader* shader)
{
    // Bind raw model
    glBindVertexArray(entity->getModel()->getVaoId());
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    // Bind texture
    ModelTexture* texture = entity->getTexture();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture->getId());
    shader->loadTexture(texture->getReflectivity(), texture->getShineDamper(), texture->getAtlasRows());

    // Disable face culling if the texture is transparent
    if (texture->getTransparency())
        glDisable(GL_CULL_FACE);
}

// Unbind an entity
void EntityRenderer::unbindEntity()
{
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glBindVertexArray(0);
}

// Sort light
void EntityRenderer::sortLight(Light* light[], int lightSize, const Entity* entity)
{
    // If light source is nearer to entity, it has higher priority
    sort(
        light, light + lightSize,
        [&](Light* a, Light* b) -> bool
        {
            float attA = a->calcAttenuation(entity->getTX(), entity->getTY(), entity->getTZ());
            float attB = b->calcAttenuation(entity->getTX(), entity->getTY(), entity->getTZ());
            return attA < attB;
        }
    );
}
