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
    
    // Render a water terrain
    static void render(const Water* water, WaterShader* shader);
    
    // Bind water quad model
    static void bindWater(const Water* water, const WaterFbo* fbo, WaterShader* shader);
    
    // Unbind water quad model
    static void unbindWater();
};

#endif
