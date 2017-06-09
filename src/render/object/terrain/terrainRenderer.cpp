#include <algorithm>

#include "utils/math/math.h"
#include "render/object/camera/camera.h"
#include "render/resource/texture/terrainTexture.h"
#include "render/object/terrain/terrainRenderer.h"

using namespace std;

// Render a terrain
void TerrainRenderer::render(const Terrain* terrain, Light* light[], int lightSize, TerrainShader* shader)
{
    // Calculate transformation matrix
    float* transMatrix = Math::createTransMatrix(
        terrain->getX(), 0, terrain->getZ(), 0, 0, 0, 1
    );
    shader->loadTransMatrix(transMatrix);

    // Sort and load light
    sortLight(light, lightSize);
    shader->loadLight(light, lightSize);

    // Bind raw model
    glBindVertexArray(terrain->getModel()->getVaoId());
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    // Draw model
    glDrawElements(GL_TRIANGLES, terrain->getModel()->getVertexCount(), GL_UNSIGNED_INT, NULL);

    // Unbind raw model
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glBindVertexArray(0);

    delete[] transMatrix;
}

// Bind a terrain
void TerrainRenderer::bindTerrain(const Terrain* terrain)
{
    // Bind terrain texture
    TerrainTexture* texture = terrain->getTexture();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture->getK());
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture->getR());
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, texture->getG());
    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, texture->getB());
    glActiveTexture(GL_TEXTURE4);
    glBindTexture(GL_TEXTURE_2D, texture->getBlend());
}

// Unbind a terrain
void TerrainRenderer::unbindTerrain()
{
    // Currently does nothing...
}

// Sort light
void TerrainRenderer::sortLight(Light* light[], int lightSize)
{
    // If light source is nearer to the camera, it has higher priority
    sort(
        light, light + lightSize,
        [](Light* a, Light* b) -> bool
        {
            float attA = a->calcAttenuation(Camera::getX(), Camera::getY(), Camera::getZ());
            float attB = b->calcAttenuation(Camera::getX(), Camera::getY(), Camera::getZ());
            return attA < attB;
        }
    );
}
