#ifndef _WATER_RENDERER_H
#define _WATER_RENDERER_H

#include "../../../glew.h"
#include "water.h"
#include "waterFbo.h"
#include "waterShader.h"

// Water renderer
class WaterRenderer
{
public:

    // DUDV map moving factor changing speed
    static const float DUDV_MOVE_SPEED;

    // Constructor
    WaterRenderer();

    // Render a water terrain
    void render(const Water* water, WaterShader* shader);

    // Bind water quad model
    void bindWater(const Water* water, const WaterFbo* fbo);

    // Unbind water quad model
    void unbindWater();

private:

    // DUDV map moving factor
    float moveFac;
};

#endif
