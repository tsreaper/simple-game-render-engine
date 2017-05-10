#include "../entities/camera.h"
#include "../../utils/math.h"
#include "skyboxRenderer.h"

// Render a skybox
void SkyboxRenderer::render(const Skybox* skybox, SkyboxShader* shader)
{
    // Bind VAO
    glBindVertexArray(skybox->getRaw()->getVaoId());
    glEnableVertexAttribArray(0);
    
    // Bind texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, skybox->getTextureId());
    
    // Calculate transformation matrix
    float* transMatrix = Math::createTransMatrix(
        Camera::getX(), Camera::getY(), Camera::getZ(), 0, skybox->getAngle(), 0, 1
    );
    shader->loadTransMatrix(transMatrix);
    
    // Draw model
    glDrawArrays(GL_TRIANGLES, 0, skybox->getRaw()->getVertexCount());
    
    // Unbind VAO
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
    
    delete[] transMatrix;
}
