#include "../models/texturedModel.h"
#include "../../utils/math.h"
#include "entityRenderer.h"

// Render an entity
void EntityRenderer::render(const Entity* entity, StaticShader* shader)
{
    // Calculate transformation matrix
    float* transMatrix = Math::createTransMatrix(
        entity->getTX(), entity->getTY(), entity->getTZ(),
        entity->getRX(), entity->getRY(), entity->getRZ(),
        entity->getScale()
    );
    shader->loadTransMatrix(transMatrix);
    
    // Draw model
    glDrawElements(GL_TRIANGLES, entity->getModel()->getRaw()->getVertexCount(), GL_UNSIGNED_INT, NULL);
    
    delete[] transMatrix;
}

// Bind a textured model
void EntityRenderer::bindTexturedModel(const TexturedModel* model, StaticShader* shader)
{
    // Bind raw model
    glBindVertexArray(model->getRaw()->getVaoId());
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    
    // Bind texture
    ModelTexture* texture = model->getTexture();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture->getId());
    shader->loadTexture(texture->getReflectivity(), texture->getShineDamper());
    
    // Disable face culling if the texture is transparent
    if (texture->getTransparency())
        glDisable(GL_CULL_FACE);
}

// Unbind a textured model
void EntityRenderer::unbindTexturedModel()
{
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glBindVertexArray(0);
}
