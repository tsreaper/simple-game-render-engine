#include <cmath>
#include <cstdlib>

#include "../render/object/camera/camera.h"
#include "../render/object/scene/scene.h"
#include "../render/object/terrain/terrain.h"
#include "../render/mainRender.h"

#include "../utils/input/keyboard.h"

#include "mainLogic.h"

Scene* scene;
Terrain* terrain;

// Initialize main logic
void MainLogic::init()
{
    // Create scene
    scene = new Scene(512, 3000, 512, 1, 1, 1, 0);
    MainRender::setScene(scene);

    // Add terrain
    terrain = scene->addTerrain("hill", 0, 0, -70, 70, "hill");

    // Add water
    scene->addWater(0, 0);

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
        scene->addEntity("pine", x, y, z, 0, rand(), 0, 3);
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
        scene->addEntity("flower", x, y, z, 0, rand(), 0, 2);
    }

    // Set initial position of camera
    Camera::incPosition(512, 10, 512);
}

// Run main logic
void MainLogic::run()
{
    // Move camera
    float yaw = Camera::getYaw();

    if (Keyboard::isKeyPressed(GLFW_KEY_W))
        Camera::incPosition((float)sin(yaw), 0, (float)-cos(yaw));
    if (Keyboard::isKeyPressed(GLFW_KEY_S))
        Camera::incPosition((float)-sin(yaw), 0, (float)cos(yaw));
    if (Keyboard::isKeyPressed(GLFW_KEY_A))
        Camera::incPosition((float)-cos(yaw), 0, (float)-sin(yaw));
    if (Keyboard::isKeyPressed(GLFW_KEY_D))
        Camera::incPosition((float)cos(yaw), 0, (float)sin(yaw));
    if (Keyboard::isKeyPressed(GLFW_KEY_I))
        Camera::incRotation(0.02, 0, 0);
    if (Keyboard::isKeyPressed(GLFW_KEY_K))
        Camera::incRotation(-0.02, 0, 0);
    if (Keyboard::isKeyPressed(GLFW_KEY_J))
        Camera::incRotation(0, -0.02, 0);
    if (Keyboard::isKeyPressed(GLFW_KEY_L))
        Camera::incRotation(0, 0.02, 0);
    if (Keyboard::isKeyPressed(GLFW_KEY_SPACE))
        Camera::incPosition(0, 0.5, 0);
    if (Keyboard::isKeyPressed(GLFW_KEY_LEFT_ALT))
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
    delete scene;
}
