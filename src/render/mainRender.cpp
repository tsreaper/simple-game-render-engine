#include <cstdlib>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include "object/entity/entity.h"
#include "object/terrain/terrain.h"
#include "object/water/water.h"
#include "object/skybox/skybox.h"

#include "../utils/math/math.h"
#include "engine/windowManager.h"
#include "object/camera/camera.h"

#include "mainRender.h"

using namespace std;

// Field of view angle
const float MainRender::FOV = 70 * 3.1415926535/180;

// Near projection plane
const float MainRender::Z_NEAR = 0.1;

// Far projection plane
const float MainRender::Z_FAR = 1000;

// Current scene
Scene* MainRender::scene = NULL;

// Renderers
EntityRenderer* MainRender::entityRenderer = NULL;
TerrainRenderer* MainRender::terrainRenderer = NULL;
WaterRenderer* MainRender::waterRenderer = NULL;
SkyboxRenderer* MainRender::skyboxRenderer = NULL;

// Shader program
EntityShader* MainRender::entityShader = NULL;
TerrainShader* MainRender::terrainShader = NULL;
WaterShader* MainRender::waterShader = NULL;
SkyboxShader* MainRender::skyboxShader = NULL;

// Water frame buffer object for water rendering
WaterFbo* MainRender::waterFbo = NULL;

// Initialize render
void MainRender::init()
{
    WindowManager::createDisplay();

    // Initialize renderers
    entityRenderer = new EntityRenderer;
    terrainRenderer = new TerrainRenderer;
    waterRenderer = new WaterRenderer;
    skyboxRenderer = new SkyboxRenderer;

    // Initialize shaders
    entityShader = new EntityShader();
    terrainShader = new TerrainShader();
    waterShader = new WaterShader();
    skyboxShader = new SkyboxShader();

    // Load projection matrix to shaders
    float* projMatrix = Math::createProjMatrix(
        1.0 * WindowManager::WINDOW_WIDTH / WindowManager::WINDOW_HEIGHT,
        FOV, Z_NEAR, Z_FAR
    );
    entityShader->start(); entityShader->loadProjMatrix(projMatrix); entityShader->stop();
    terrainShader->start(); terrainShader->loadProjMatrix(projMatrix); terrainShader->stop();
    waterShader->start(); waterShader->loadProjMatrix(projMatrix); waterShader->stop();
    skyboxShader->start(); skyboxShader->loadProjMatrix(projMatrix); skyboxShader->stop();

    delete[] projMatrix;

    // Initialize water FBO
    waterFbo = new WaterFbo();
}

// Main render process
void MainRender::render()
{
    if (scene == NULL)
    {
        cerr << "No scene to render!" << endl;
        exit(-1);
    }

    // Calculate camera matrix
    float* cameraMatrix = Math::createTransMatrix(
        -Camera::getX(), -Camera::getY(), -Camera::getZ(),
        -Camera::getPitch(), Camera::getYaw(), Camera::getRoll(), 1, true
    );
    float* reflectionCameraMatrix = Math::createTransMatrix(
        -Camera::getX(), Camera::getY() - 2*scene->getWaterHeight(), -Camera::getZ(),
        Camera::getPitch(), Camera::getYaw(), Camera::getRoll(), 1, true
    );

    // Render scene
    renderWithoutWater(cameraMatrix);
    renderWater(cameraMatrix, reflectionCameraMatrix);

    // Update scene
    scene->update();

    WindowManager::updateDisplay();
    WindowManager::updateFps();
    delete[] cameraMatrix;
    delete[] reflectionCameraMatrix;
}

void MainRender::cleanUp()
{
    // Clean up waterFBO
    delete waterFbo;

    // Clean up renderers
    delete entityRenderer;
    delete terrainRenderer;
    delete waterRenderer;
    delete skyboxRenderer;

    // Clean up shaders
    delete entityShader;
    delete terrainShader;
    delete waterShader;
    delete skyboxShader;

    WindowManager::destroyDisplay();
}

// Get current scene
Scene* MainRender::getScene()
{
    return scene;
}

// Set current scene
void MainRender::setScene(Scene* _scene)
{
    scene = _scene;
}

// Render everything except water
void MainRender::renderWithoutWater(const float* cameraMatrix, float clipHeight, bool clipPositive)
{
    // Prepare to render
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.61, 0.76, 0.88, 1);

    // Render entities
    const unordered_map<string, unordered_set<Entity*>>* entityMap = scene->getAllEntities();
    prepareShader(entityShader, cameraMatrix, clipHeight, clipPositive);
    for (auto entitySet : *entityMap)
    {
        entityRenderer->bindEntity(*(entitySet.second.begin()), entityShader);
        for (auto entity : entitySet.second)
            entityRenderer->render(entity, entityShader);
        entityRenderer->unbindEntity();
    }
    entityShader->stop();

    // Render terrains
    const unordered_map<string, unordered_set<Terrain*>>* terrainMap = scene->getAllTerrains();
    prepareShader(terrainShader, cameraMatrix, clipHeight, clipPositive);
    for (auto terrainSet : *terrainMap)
    {
        terrainRenderer->bindTerrain(*(terrainSet.second.begin()));
        for (auto terrain : terrainSet.second)
            terrainRenderer->render(terrain, terrainShader);
        terrainRenderer->unbindTerrain();
    }
    terrainShader->stop();

    // Render skybox
    Skybox* skybox = scene->getSkybox();
    prepareShader(skyboxShader, cameraMatrix, clipHeight, clipPositive);
    skyboxRenderer->render(skybox, skyboxShader);
    skyboxShader->stop();
}

// Render water only
void MainRender::renderWater(const float* cameraMatrix, const float* reflectionCameraMatrix)
{
    // Render water refraction effect
    waterFbo->bindRefractionFbo();
    renderWithoutWater(cameraMatrix, scene->getWaterHeight() + 1, true);
    waterFbo->unbindFbo();

    // Render water reflection effect
    waterFbo->bindReflectionFbo();
    renderWithoutWater(reflectionCameraMatrix, scene->getWaterHeight() - 1, false);
    waterFbo->unbindFbo();

    // Render water
    const unordered_set<Water*>* waterSet = scene->getAllWater();
    prepareShader(waterShader, cameraMatrix);
    if (!waterSet->empty())
    {
        waterRenderer->bindWater(*(waterSet->begin()), waterFbo);
        for (auto water : *waterSet)
            waterRenderer->render(water, waterShader);
        waterRenderer->unbindWater();
    }
}

// Prepare shader for rendering
void MainRender::prepareShader(BasicShader* shader, const float* cameraMatrix, float clipHeight, bool clipPositive)
{
    shader->start();
    shader->loadCameraMatrix(cameraMatrix);
    shader->loadSkyCol(0.61, 0.76, 0.88);
    shader->loadLight(scene->getSun());
    shader->loadClipping(clipHeight, clipPositive);
}
