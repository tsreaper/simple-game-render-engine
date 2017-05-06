#include <iostream>
#include "../textures/texturePack.h"
#include "../../utils/math.h"
#include "terrainRenderer.h"

using namespace std;

// Render a terrain
void TerrainRenderer::render(const Terrain* terrain, TerrainShader* shader)
{
    // Calculate transformation matrix
    float* transMatrix = Math::createTransMatrix(
        terrain->getX(), 0, terrain->getZ(), 0, 0, 0, 1
    );
    shader->loadTransMatrix(transMatrix);
    
    // Draw model
    glDrawElements(GL_TRIANGLES, terrain->getRaw()->getVertexCount(), GL_UNSIGNED_INT, NULL);
    
    delete[] transMatrix;
}

// Bind a terrain
void TerrainRenderer::bindTerrain(const Terrain* terrain, TerrainShader* shader)
{
    // Bind raw model
    glBindVertexArray(terrain->getRaw()->getVaoId());
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    
    // Bind texture pack
    TexturePack* pack = terrain->getTexturePack();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, pack->getK()->getId());
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, pack->getR()->getId());
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, pack->getG()->getId());
    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, pack->getB()->getId());
    glActiveTexture(GL_TEXTURE4);
    glBindTexture(GL_TEXTURE_2D, pack->getBlend()->getId());
}

// Unbind a terrain
void TerrainRenderer::unbindTerrain()
{
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glBindVertexArray(0);
}
