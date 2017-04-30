#include "../../utils/math.h"
#include "windowManager.h"
#include "../models/rawModel.h"
#include "../models/texturedModel.h"
#include "../entities/camera.h"
#include "renderer.h"

// Field of view angle
const float Renderer::FOV = 70 * 3.1415926535/180;

// Near projection plane
const float Renderer::Z_NEAR = 0.1;

// Far projection plane
const float Renderer::Z_FAR = 100;

// Clear screen and prepare to render
void Renderer::prepare()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0, 0.05, 0.2, 1);
}

// Render an entity
void Renderer::render(const Entity* entity, StaticShader* shader)
{
    // Calculate transformation matrix
    float* transMatrix = Math::createTransMatrix(
        entity->getTX(), entity->getTY(), entity->getTZ(),
        entity->getRX(), entity->getRY(), entity->getRZ(),
        entity->getScale()
    );
    shader->loadTransMatrix(transMatrix);
    
    // Calculate camera matrix
    float* cameraMatrix = Math::createTransMatrix(
        -Camera::getX(), -Camera::getY(), -Camera::getZ(),
        -Camera::getPitch(), Camera::getYaw(), Camera::getRoll(), 1
    );
    shader->loadCameraMatrix(cameraMatrix);
    
    // Calculate projection matrix
    float* projMatrix = Math::createProjMatrix(
        1.0 * WindowManager::WINDOW_WIDTH / WindowManager::WINDOW_HEIGHT,
        FOV, Z_NEAR, Z_FAR
    );
    shader->loadProjMatrix(projMatrix);
    
    // Draw model
    glDrawElements(GL_TRIANGLES, entity->getModel()->getRaw()->getVertexCount(), GL_UNSIGNED_INT, NULL);
    
    // Clean up matrices
    delete[] transMatrix;
    delete[] cameraMatrix;
    delete[] projMatrix;
}

// Bind a textured model
void Renderer::bindTexturedModel(const TexturedModel* model, StaticShader* shader)
{
    // Bind raw model
    RawModel* raw = model->getRaw();
    glBindVertexArray(raw->getVaoId());
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    
    // Bind texture
    ModelTexture* texture = model->getTexture();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture->getId());
    shader->loadReflectivity(texture->getReflectivity());
    shader->loadShineDamper(texture->getShineDamper());
}

// Unbind a textured model
void Renderer::unbindTexturedModel()
{
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
}
