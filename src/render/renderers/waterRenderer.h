#ifndef WATER_RENDERER_H_
#define WATER_RENDERER_H_

#include "../../glew.h"
#include "../terrains/water.h"
#include "../textures/waterFbo.h"
#include "../shaders/waterShader.h"

// Water renderer
class WaterRenderer
{
public:
    
    // DUDV map moving factor changing speed
    static const float DUDV_MOVE_SPEED;
    
    // Render a water terrain
    static void render(const Water* water, WaterShader* shader);
    
    // Bind water quad model
    static void bindWater(const Water* water, const WaterFbo* fbo, WaterShader* shader);
    
    // Unbind water quad model
    static void unbindWater();
    
private:
    
    // DUDV map moving factor
    static float moveFac;
};

#endif
