#include "../../../utils/math/math.h"
#include "../../resource/texture/modelTexture.h"
#include "entityRenderer.h"

// Render an entity
void EntityRenderer::render(const Entity* entity, EntityShader* shader)
{
    // Calculate transformation matrix
    float* transMatrix = Math::createTransMatrix(
        entity->getTX(), entity->getTY(), entity->getTZ(),
        entity->getRX(), entity->getRY(), entity->getRZ(),
        entity->getScale()
    );
    shader->loadTransMatrix(transMatrix);

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
    shader->loadTexture(texture->getReflectivity(), texture->getShineDamper());

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
