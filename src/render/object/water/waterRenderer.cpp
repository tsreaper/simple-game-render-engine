#include "../../../utils/math/math.h"
#include "waterRenderer.h"

// DUDV map moving factor changing speed
const float WaterRenderer::DUDV_MOVE_SPEED = 0.0005;

// Constructor
WaterRenderer::WaterRenderer()
{
    // DUDV map moving factor
    moveFac = 0;
}

// Render a water terrain
void WaterRenderer::render(const Water* water, WaterShader* shader)
{
    // Calculate transformation matrix
    float* transMatrix = Math::createTransMatrix(
        water->getX(), water->getY(), water->getZ(), 0, 0, 0, 1
    );
    shader->loadTransMatrix(transMatrix);

    // Change and load the DUDV map moving factor
    moveFac += DUDV_MOVE_SPEED;
    if (moveFac >= 1)
        moveFac = 0;
    shader->loadMoveFac(moveFac);

    // Draw water quad
    glDrawArrays(GL_TRIANGLE_STRIP, 0, water->getModel()->getVertexCount());

    delete[] transMatrix;
}

// Bind water quad model
void WaterRenderer::bindWater(const Water* water, const WaterFbo* fbo)
{
    // Bind raw model
    glBindVertexArray(water->getModel()->getVaoId());
    glEnableVertexAttribArray(0);

    // Bind texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, fbo->getReflectionTex());
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, fbo->getRefractionTex());
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, water->getDudv()->getId());
    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, water->getNorm()->getId());
    glActiveTexture(GL_TEXTURE4);
    glBindTexture(GL_TEXTURE_2D, fbo->getRefractionDepth());
}

// Unbind water quad model
void WaterRenderer::unbindWater()
{
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
}