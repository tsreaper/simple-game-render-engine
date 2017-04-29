#include "../../glew.h"
#include "../../utils/math.h"
#include "displayManager.h"
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

// Shader program used for rendering
StaticShader* Renderer::shader = NULL;

// Clear screen and prepare to render
void Renderer::prepare()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0, 0.05, 0.2, 1);
}

// Render a model
void Renderer::render(const Entity* entity, const Light* light)
{
    shader->start();
    
    TexturedModel* model = entity->getModel();
    RawModel* raw = model->getRaw();
    
    // Enable positions, texture coordinates and normal vectors
    glBindVertexArray(raw->getVaoId());
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, model->getTexture()->getId());
    
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
        1.0 * DisplayManager::DISPLAY_WIDTH / DisplayManager::DISPLAY_HEIGHT,
        FOV, Z_NEAR, Z_FAR
    );
    shader->loadProjMatrix(projMatrix);
    
    // Load light
    shader->loadLightPos(light->getX(), light->getY(), light->getZ());
    shader->loadLightCol(light->getR(), light->getG(), light->getB());
    
    // Load texture reflectivity
    shader->loadReflectivity(model->getTexture()->getReflectivity());
    shader->loadShineDamper(model->getTexture()->getShineDamper());
    
    // Draw model
    glDrawElements(GL_TRIANGLES, raw->getVertexCount(), GL_UNSIGNED_INT, NULL);
    
    // Disable positions, texture coordinates and normal vectors
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
    
    shader->stop();
    
    // Clean up matrices
    delete[] transMatrix;
    delete[] cameraMatrix;
    delete[] projMatrix;
}

// Set current shader
void Renderer::setShader(StaticShader* _shader)
{
    shader = _shader;
}
