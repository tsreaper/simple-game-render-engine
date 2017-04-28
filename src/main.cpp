#include "glew.h"
#include "render/renderEngine/displayManager.h"
#include "render/renderEngine/loader.h"
#include "render/renderEngine/renderer.h"
#include "render/shaders/staticShader.h"
#include "render/models/rawModel.h"
#include "render/models/texturedModel.h"
#include "render/entities/entity.h"
#include "logic/gameLogic.h"

float verticies[] = {
    -0.5f, 0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    0.5f, -0.5f, -0.5f,
    0.5f, 0.5f, -0.5f,
    
    -0.5f, 0.5f, 0.5f,
    -0.5f, -0.5f, 0.5f,
    0.5f, -0.5f, 0.5f,
    0.5f, 0.5f, 0.5f,
    
    0.5f, 0.5f, -0.5f,
    0.5f, -0.5f, -0.5f,
    0.5f, -0.5f, 0.5f,
    0.5f, 0.5f, 0.5f,
    
    -0.5f, 0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f, 0.5f,
    -0.5f, 0.5f, 0.5f,
    
    -0.5f, 0.5f, 0.5f,
    -0.5f, 0.5f, -0.5f,
    0.5f, 0.5f, -0.5f,
    0.5f, 0.5f, 0.5f,
    
    -0.5f, -0.5f, 0.5f,
    -0.5f, -0.5f, -0.5f,
    0.5f, -0.5f, -0.5f,
    0.5f, -0.5f, 0.5f
};
int indicies[] = {
    0, 1, 3,
    3, 1, 2,
    4, 5, 7,
    7, 5, 6,
    8, 9, 11,
    11, 9, 10,
    12, 13, 15,
    15, 13, 14,
    16, 17, 19,
    19, 17, 18,
    20, 21, 23,
    23, 21, 22
};
float texCoords[] = {
    0, 0,
    0, 1,
    1, 1,
    1, 0,
    0, 0,
    0, 1,
    1, 1,
    1, 0,
    0, 0,
    0, 1,
    1, 1,
    1, 0,
    0, 0,
    0, 1,
    1, 1,
    1, 0,
    0, 0,
    0, 1,
    1, 1,
    1, 0,
    0, 0,
    0, 1,
    1, 1,
    1, 0
};

int main (int argc,  char** argv)
{
    DisplayManager::createDisplay();
    
    StaticShader shader;
    Renderer::setShader(&shader);
    
    RawModel raw = Loader::loadToVao(verticies, 72, texCoords, 48, indicies, 36);
    ModelTexture texture(Loader::loadTexture("res/sample.png"));
    TexturedModel model(&raw, &texture);
    Entity entity(&model, 0, 0, -3);
    
    while (!DisplayManager::isExiting())
    {
        GameLogic::run();
        entity.incRotation(0.07, -0.05, 0.03);
        Renderer::prepare();
        Renderer::render(&entity);
        DisplayManager::updateDisplay();
    }
    
    shader.cleanUp();
    Loader::cleanUp();
    DisplayManager::destroyDisplay();
    
    return 0;
}
