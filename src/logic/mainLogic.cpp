#include <cstdlib>
#include "../render/mainRender.h"
#include "../render/renderEngine/windowManager.h"
#include "../render/entities/entity.h"
#include "../render/entities/light.h"
#include "../render/entities/camera.h"
#include "mainLogic.h"

Entity* entity[10];

// Initialize main logic
void MainLogic::init()
{
    for (int i = 0; i < 10; i++)
    {
        entity[i] = MainRender::createEntity("dragon");
        entity[i]->incPosition(0, rand()%10-5, -rand()%50);
        entity[i]->incRotation(rand(), rand(), rand());
    }
    MainRender::loadLight(new Light(100, 100, 200, 1, 1, 1));
}

// Run main logic
void MainLogic::run()
{
    for (int i = 0; i < 10; i++)
        entity[i]->incRotation(0, 0.05, 0);
    
    if (WindowManager::isKeyPressed(GLFW_KEY_W))
        Camera::incPosition(0, 0, -0.1);
    if (WindowManager::isKeyPressed(GLFW_KEY_S))
        Camera::incPosition(0, 0, 0.1);
    if (WindowManager::isKeyPressed(GLFW_KEY_A))
        Camera::incPosition(-0.1, 0, 0);
    if (WindowManager::isKeyPressed(GLFW_KEY_D))
        Camera::incPosition(0.1, 0, 0);
}

// Clean up
void MainLogic::cleanUp()
{
    for (int i = 0; i < 10; i++)
        MainRender::destroyEntity(entity[i]);
}
