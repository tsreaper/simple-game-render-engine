#include <cmath>
#include <cstdlib>
#include <ctime>

#include "utils/struct/struct.h"
#include "utils/input/keyboard.h"

#include "render/object/camera/camera.h"
#include "render/object/scene/scene.h"
#include "render/object/light/light.h"
#include "render/object/terrain/terrain.h"
#include "render/engine/windowManager.h"
#include "render/mainRender.h"

#include "logic/mainLogic.h"

Scene* scene;
Terrain* terrain;

int minute;
Light* sun;
Light* moon;
Light* camLight;

// Initialize main logic
void MainLogic::init()
{
    // srand(time(0));

    // Create scene
    scene = new Scene(0);
    MainRender::setScene(scene);

    // Add terrain
    terrain = scene->addTerrain("hill", 0, 0, -120, 120, "hill");

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
        scene->addEntity("pine", vec3(x, y, z), vec3(0, rand(), 0), 1.5 * rand() / RAND_MAX + 2);
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
        scene->addEntity("flower", vec3(x, y, z), vec3(0, rand(), 0), 2);
    }

    // Add some ferns
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
        scene->addEntity("fern", vec3(x, y, z), vec3(0, rand(), 0), 1, rand()%4);
    }
    
    // Add some boulders
    for (int i = 0; i < 30; i++)
    {
        float x, y, z;
        do
        {
            x = 1.0 * rand() / RAND_MAX * 1024;
            z = 1.0 * rand() / RAND_MAX * 1024;
            y = terrain->getHeight(x, z);
        }
        while (y < 0);
        scene->addEntity("boulder", vec3(x, y, z), vec3(0, rand(), 0), 0.5 * rand() / RAND_MAX + 0.3);
    }
    
    // Add statue
    for (int i = 0; i < 3; i++)
    {
        float x, y, z;
        do
        {
            x = 1.0 * rand() / RAND_MAX * 1024;
            z = 1.0 * rand() / RAND_MAX * 1024;
            y = terrain->getHeight(x, z);
        }
        while (y < 30);
        scene->addEntity("statue", vec3(x, y, z), vec3(0, rand(), 0), 3);
    }

    // Add random light sources
    for (int i = 0; i < 20; i++)
    {
        float x, y, z;
        do
        {
            x = 1.0 * rand() / RAND_MAX * 1024;
            z = 1.0 * rand() / RAND_MAX * 1024;
            y = terrain->getHeight(x, z);
        }
        while (y < 0);

        float r, g, b;
        int rnd = rand() % 7 + 1;
        r = rnd & 1;
        g = rnd>>1 & 1;
        b = rnd>>2 & 1;
        
        if (rand() & 1)
        {
            scene->addEntity("lamp", vec3(x, y, z));
            scene->addLight(vec3(x, y + 14.7, z), vec3(r, g, b), vec3(1, 0.005, 0.001));
        }
        else
        {
            scene->addEntity("lantern", vec3(x, y, z), vec3(0, rand(), 0), 0.7);
            scene->addLight(vec3(x, y + 15, z), vec3(r, g, b), vec3(1, 0.005, 0.001));
        }
    }

    // Add sun and moon
    sun = scene->addLight(vec3(512, 3000, 512), vec3(0, 0, 0));
    // moon = scene->addLight(vec3(0, 0, 0), vec3(0, 0, 0));
    
    // Add camera light
    camLight = scene->addLight(vec3(512, 10, 512), vec3(1, 1, 1), vec3(1, 0.005, 0.001));

    // Set initial position of camera
    Camera::incPos(512, 10, 512);

    // Set scene logic
    minute = 7 * 60 * 3;
}

// Run main logic
void MainLogic::run()
{
    // Move camera
    float yaw = Camera::getRot().y;

    if (Keyboard::isKeyPressed(GLFW_KEY_W))
        Camera::incPos((float)-sin(yaw) * 0.7, 0, (float)-cos(yaw) * 0.7);
    if (Keyboard::isKeyPressed(GLFW_KEY_S))
        Camera::incPos((float)sin(yaw) * 0.7, 0, (float)cos(yaw) * 0.7);
    if (Keyboard::isKeyPressed(GLFW_KEY_A))
        Camera::incPos((float)-cos(yaw) * 0.7, 0, (float)sin(yaw) * 0.7);
    if (Keyboard::isKeyPressed(GLFW_KEY_D))
        Camera::incPos((float)cos(yaw) * 0.7, 0, (float)-sin(yaw) * 0.7);
    if (Keyboard::isKeyPressed(GLFW_KEY_I))
        Camera::incRot(0.02, 0, 0);
    if (Keyboard::isKeyPressed(GLFW_KEY_K))
        Camera::incRot(-0.02, 0, 0);
    if (Keyboard::isKeyPressed(GLFW_KEY_J))
        Camera::incRot(0, 0.02, 0);
    if (Keyboard::isKeyPressed(GLFW_KEY_L))
        Camera::incRot(0, -0.02, 0);
    if (Keyboard::isKeyPressed(GLFW_KEY_SPACE))
        Camera::incPos(0, 0.5, 0);
    if (Keyboard::isKeyPressed(GLFW_KEY_LEFT_ALT))
        Camera::incPos(0, -0.5, 0);
    if (Keyboard::isKeyPressed(GLFW_KEY_KP_ADD))
        scene->setWaterHeight(scene->getWaterHeight() + 0.3);
    if (Keyboard::isKeyPressed(GLFW_KEY_KP_SUBTRACT))
        scene->setWaterHeight(scene->getWaterHeight() - 0.3);

    vec3 pos = Camera::getPos();
    pos.x = min(max(pos.x, 0.0f), 1024.0f);
    pos.z = min(max(pos.z, 0.0f), 1024.0f);
    pos.y = max(max(pos.y, terrain->getHeight(pos.x, pos.z) + 5), scene->getWaterHeight() + 1);
    Camera::setPos(pos);
    
    // Set camera light pos
    camLight->setPos(pos);

    // Day/Night logic
    minute++;
    if (minute >= 24 * 60 * 3)
        minute = 0;

    float nightFac;
    if (minute < 5 * 60 * 3)
        nightFac = 1;
    else if (minute < 7 * 60 * 3)
        nightFac = 1 - 1.0 * (minute - 5 * 60 * 3) / (2 * 60 * 3);
    else if (minute < 17 * 60 * 3)
        nightFac = 0;
    else if (minute < 19 * 60 * 3)
        nightFac = 1.0 * (minute - 17 * 60 * 3) / (2 * 60 * 3);
    else
        nightFac = 1;
    scene->getSkybox()->setNightFac(nightFac);
    scene->setSkyCol(vec3(1 - nightFac, 1 - nightFac, 1 - nightFac));
    sun->setCol(vec3(1 - nightFac*0.6, 1 - nightFac*0.6, 1 - nightFac*0.6));

    // Take screenshot
    if (Keyboard::isKeyPressed(GLFW_KEY_T))
        WindowManager::takeScreenshot("screenshot");
}

// Clean up
void MainLogic::cleanUp()
{
    delete scene;
}
