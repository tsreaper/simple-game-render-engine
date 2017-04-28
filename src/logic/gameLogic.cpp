#include <GLFW/glfw3.h>
#include "../render/renderEngine/displayManager.h"
#include "../render/entities/camera.h"
#include "gameLogic.h"

// Run game logic
void GameLogic::run()
{
    if (DisplayManager::isKeyPressed(GLFW_KEY_W))
        Camera::incPosition(0, 0, -0.1);
    if (DisplayManager::isKeyPressed(GLFW_KEY_S))
        Camera::incPosition(0, 0, 0.1);
    if (DisplayManager::isKeyPressed(GLFW_KEY_A))
        Camera::incPosition(-0.1, 0, 0);
    if (DisplayManager::isKeyPressed(GLFW_KEY_D))
        Camera::incPosition(0.1, 0, 0);
}
