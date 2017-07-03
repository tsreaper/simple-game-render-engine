#include "utils/math/math.h"
#include "utils/struct/struct.h"

#include "render/object/camera/camera.h"
#include "render/object/skybox/skyboxRenderer.h"

// Render a skybox
void SkyboxRenderer::render(const Skybox* skybox, SkyboxShader* shader)
{
    // Calculate transformation matrix
    float* transMatrix = Math::createTransMatrix(
        Camera::getPos(), vec3(0, skybox->getAngle(), 0), 1
    );
    shader->loadTransMatrix(transMatrix);

    // Bind VAO
    glBindVertexArray(skybox->getModel()->getVaoId());
    glEnableVertexAttribArray(0);

    // Bind texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, skybox->getDayTexture()->getId());
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_CUBE_MAP, skybox->getNightTexture()->getId());

    // Set night factor
    shader->loadNightFac(skybox->getNightFac());

    // Draw model
    glDrawArrays(GL_TRIANGLES, 0, skybox->getModel()->getVertexCount());

    // Unbind VAO
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);

    delete[] transMatrix;
}
