#include "engine/windowManager.h"
#include "engine/memoryManager.h"
#include "entities/camera.h"
#include "renderers/entityRenderer.h"
#include "renderers/terrainRenderer.h"
#include "renderers/waterRenderer.h"
#include "renderers/skyboxRenderer.h"
#include "../utils/math.h"
#include "mainRender.h"

using namespace std;

// Field of view angle
const float MainRender::FOV = 70 * 3.1415926535/180;

// Near projection plane
const float MainRender::Z_NEAR = 0.1;

// Far projection plane
const float MainRender::Z_FAR = 1000;

// Objects being rendered
unordered_map<string, unordered_set<Entity*>> MainRender::entityMap;
unordered_set<Terrain*> MainRender::terrainSet;
unordered_set<Water*> MainRender::waterSet;
Skybox* MainRender::skybox = NULL;

// Shader program
StaticShader* MainRender::staticShader = NULL;
TerrainShader* MainRender::terrainShader = NULL;
WaterShader* MainRender::waterShader = NULL;
SkyboxShader* MainRender::skyboxShader = NULL;

// Light in the 3D world
Light* MainRender::light = NULL;

// Initialize render
void MainRender::init()
{
    WindowManager::createDisplay();
    MemoryManager::init();
    
    // Initialize shaders
    staticShader = new StaticShader();
    terrainShader = new TerrainShader();
    waterShader = new WaterShader();
    skyboxShader = new SkyboxShader();
    
    // Load projection matrix to shaders
    float* projMatrix = Math::createProjMatrix(
        1.0 * WindowManager::WINDOW_WIDTH / WindowManager::WINDOW_HEIGHT,
        FOV, Z_NEAR, Z_FAR
    );
    staticShader->start(); staticShader->loadProjMatrix(projMatrix); staticShader->stop();
    terrainShader->start(); terrainShader->loadProjMatrix(projMatrix); terrainShader->stop();
    waterShader->start(); waterShader->loadProjMatrix(projMatrix); waterShader->stop();
    skyboxShader->start(); skyboxShader->loadProjMatrix(projMatrix); skyboxShader->stop();
    
    delete[] projMatrix;
    
    // Initialize skybox
    skybox = new Skybox();
}

// Main render process
void MainRender::render()
{
    // Prepare to render
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.61, 0.76, 0.88, 1);
    
    // Calculate camera matrix
    float* cameraMatrix = Math::createTransMatrix(
        -Camera::getX(), -Camera::getY(), -Camera::getZ(),
        -Camera::getPitch(), Camera::getYaw(), Camera::getRoll(), 1, true
    );
    
    // Prepare static shader
    staticShader->start();
    staticShader->loadCameraMatrix(cameraMatrix);
    staticShader->loadSkyCol(0.61, 0.76, 0.88);
    
    // Render entities
    for (auto entitySet : entityMap)
    {
        EntityRenderer::bindTexturedModel((*(entitySet.second.begin()))->getModel(), staticShader);
        for (auto entity : entitySet.second)
            EntityRenderer::render(entity, staticShader);
        EntityRenderer::unbindTexturedModel();
    }
    staticShader->stop();
    
    // Prepare terrain shader
    terrainShader->start();
    terrainShader->loadCameraMatrix(cameraMatrix);
    terrainShader->loadSkyCol(0.61, 0.76, 0.88);
    
    // Render terrains
    for (auto terrain : terrainSet)
    {
        TerrainRenderer::bindTerrain(terrain, terrainShader);
        TerrainRenderer::render(terrain, terrainShader);
        TerrainRenderer::unbindTerrain();
    }
    terrainShader->stop();
    
    // Prepare water shader
    waterShader->start();
    waterShader->loadCameraMatrix(cameraMatrix);
    waterShader->loadSkyCol(0.61, 0.76, 0.88);
    
    // Render waters
    if (!waterSet.empty())
    {
        WaterRenderer::bindWater(*(waterSet.begin()), waterShader);
        for (auto water : waterSet)
            WaterRenderer::render(water, waterShader);
        WaterRenderer::unbindWater();
    }
    
    // Prepare skybox shader
    skyboxShader->start();
    skyboxShader->loadCameraMatrix(cameraMatrix);
    skyboxShader->loadSkyCol(0.61, 0.76, 0.88);
    
    // Render skybox
    SkyboxRenderer::render(skybox, skyboxShader);
    skyboxShader->stop();
    skybox->rotate();
    
    WindowManager::updateDisplay();
    delete[] cameraMatrix;
}

// Create an entity in the 3D world
Entity* MainRender::createEntity(const char* name)
{
    // Create entity
    Entity* entity = new Entity(MemoryManager::getTexturedModel(name));
    
    // Record entity into map
    if (entityMap.find(name) == entityMap.end())
        entityMap[name] = unordered_set<Entity*>();
    entityMap[name].insert(entity);
    
    return entity;
}

// Create a terrain in the 3D world
Terrain* MainRender::createTerrain(const char* name, int gridX, int gridZ)
{
    // Create terrain
    Terrain* terrain = new Terrain(gridX, gridZ, MemoryManager::getTexturePack(name), -70, 70, "terrains/heightMap.png");
    
    // Record terrain into set
    terrainSet.insert(terrain);
    
    return terrain;
}

// Create a water terrain in the 3D world
Water* MainRender::createWater(int gridX, int gridZ, float y)
{
    // Create water
    Water* water = new Water(gridX, gridZ, y);
    
    // Record water into set
    waterSet.insert(water);
    
    return water;
}

// Remove the entity from the 3D world
void MainRender::destroyEntity(Entity* entity)
{
    unordered_set<Entity*>& entitySet = entityMap[entity->getModel()->getName()];
    entitySet.erase(entity);
    if (entitySet.empty())
        entityMap.erase(entity->getModel()->getName());
    delete entity;
}

// Remove the terrain from the 3D world
void MainRender::destroyTerrain(Terrain* terrain)
{
    terrainSet.erase(terrain);
    delete terrain;
}

// Remove the water terrain from the 3D world
void MainRender::destroyWater(Water* water)
{
    waterSet.erase(water);
    delete water;
}

// Load light
void MainRender::loadLight(Light* _light)
{
    light = _light;
    
    staticShader->start();
    staticShader->loadLight(
        light->getX(), light->getY(), light->getZ(),
        light->getR(), light->getG(), light->getB()
    );
    staticShader->stop();
    
    terrainShader->start();
    terrainShader->loadLight(
        light->getX(), light->getY(), light->getZ(),
        light->getR(), light->getG(), light->getB()
    );
    terrainShader->stop();
}

// Clean up
void MainRender::cleanUp()
{
    // Clean up entities
    for (auto entitySet : entityMap)
        for (auto entity : entitySet.second)
            destroyEntity(entity);
    
    // Clean up terrains
    for (auto terrain : terrainSet)
        destroyTerrain(terrain);
    
    // Clean up water
    for (auto water : waterSet)
        destroyWater(water);
    
    // Clean up skybox
    delete skybox;
    
    // Clean up light
    delete light;
    
    // Clean up shaders
    staticShader->cleanUp();
    delete staticShader;
    terrainShader->cleanUp();
    delete terrainShader;
    waterShader->cleanUp();
    delete waterShader;
    
    WindowManager::destroyDisplay();
}
