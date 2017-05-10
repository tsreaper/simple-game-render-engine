#include "../../utils/math.h"
#include "waterRenderer.h"

// Render a water terrain
void WaterRenderer::render(const Water* water, WaterShader* shader)
{
    // Calculate transformation matrix
    float* transMatrix = Math::createTransMatrix(
        water->getX(), water->getY(), water->getZ(), 0, 0, 0, 1
    );
    shader->loadTransMatrix(transMatrix);
    
    // Draw water quad
    glDrawArrays(GL_TRIANGLE_STRIP, 0, water->getRaw()->getVertexCount());
    
    delete[] transMatrix;
}

// Bind water quad model
void WaterRenderer::bindWater(const Water* water, WaterShader* shader)
{
    // Bind raw model
    glBindVertexArray(water->getRaw()->getVaoId());
    glEnableVertexAttribArray(0);
}

// Unbind water quad model
void WaterRenderer::unbindWater()
{
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
}
