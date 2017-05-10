#include <cmath>
#include <cstdlib>
#include <vector>
#include "../render/mainRender.h"
#include "../render/engine/windowManager.h"
#include "../render/entities/entity.h"
#include "../render/entities/light.h"
#include "../render/entities/camera.h"
#include "../render/terrains/terrain.h"
#include "../render/terrains/water.h"
#include "mainLogic.h"

using namespace std;

vector<Entity*> entityVec;
Terrain* terrain;
Water* water;

// Initialize main logic
void MainLogic::init()
{
    // Add sun light
    MainRender::loadLight(new Light(512, 3000, 512, 1, 1, 1));
    
    // Add terrain
    terrain = MainRender::createTerrain("hill", 0, 0);
    
    // Add water
    water = MainRender::createWater(0, 0, 0);
    
    // Add some trees
    for (int i = 0; i < 100; i++)
    {
        float x, y, z;
        do
        {
            x = 1.0 * rand() / RAND_MAX * 1024;
            z = 1.0 * rand() / RAND_MAX * 1024;
            y = terrain->getHeight(x, z);
        }
        while (y < 0);
        
        Entity* tree = MainRender::createEntity("pine");
        tree->incPosition(x, y, z);
        tree->incRotation(0, rand(), 0);
        tree->setScale(3);
        entityVec.push_back(tree);
    }
    
    // Add some flowers
    for (int i = 0; i < 300; i++)
    {
        float x, y, z;
        do
        {
            x = 1.0 * rand() / RAND_MAX * 1024;
            z = 1.0 * rand() / RAND_MAX * 1024;
            y = terrain->getHeight(x, z);
        }
        while (y < 0);
        
        Entity* flower = MainRender::createEntity("flower");
        flower->incPosition(x, y, z);
        flower->incRotation(0, rand(), 0);
        flower->setScale(2);
        entityVec.push_back(flower);
    }
    
    // Set initial position of camera
    Camera::incPosition(512, 0, 512);
}

// Run main logic
void MainLogic::run()
{
    // Move camera
    float yaw = Camera::getYaw();
    
    if (WindowManager::isKeyPressed(GLFW_KEY_W))
        Camera::incPosition((float)sin(yaw), 0, (float)-cos(yaw));
    if (WindowManager::isKeyPressed(GLFW_KEY_S))
        Camera::incPosition((float)-sin(yaw), 0, (float)cos(yaw));
    if (WindowManager::isKeyPressed(GLFW_KEY_A))
        Camera::incPosition((float)-cos(yaw), 0, (float)-sin(yaw));
    if (WindowManager::isKeyPressed(GLFW_KEY_D))
        Camera::incPosition((float)cos(yaw), 0, (float)sin(yaw));
    if (WindowManager::isKeyPressed(GLFW_KEY_I))
        Camera::incRotation(0.02, 0, 0);
    if (WindowManager::isKeyPressed(GLFW_KEY_K))
        Camera::incRotation(-0.02, 0, 0);
    if (WindowManager::isKeyPressed(GLFW_KEY_J))
        Camera::incRotation(0, -0.02, 0);
    if (WindowManager::isKeyPressed(GLFW_KEY_L))
        Camera::incRotation(0, 0.02, 0);
    if (WindowManager::isKeyPressed(GLFW_KEY_SPACE))
        Camera::incPosition(0, 0.5, 0);
    if (WindowManager::isKeyPressed(GLFW_KEY_LEFT_ALT))
        Camera::incPosition(0, -0.5, 0);
    
    float x = Camera::getX(), y = Camera::getY(), z = Camera::getZ();
    x = min(max(x, 0.0f), 1024.0f);
    z = min(max(z, 0.0f), 1024.0f);
    y = max(y, terrain->getHeight(x, z) + 5);
    Camera::setX(x); Camera::setY(y); Camera::setZ(z);
}

// Clean up
void MainLogic::cleanUp()
{
    // Delete entities
    for (int i = 0; i < entityVec.size(); i++)
        MainRender::destroyEntity(entityVec[i]);
    
    // Delete terrain
    MainRender::destroyTerrain(terrain);
    
    // Delete water
    MainRender::destroyWater(water);
}
