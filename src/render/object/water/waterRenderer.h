#ifndef _WATER_RENDERER_H
#define _WATER_RENDERER_H

#include "glew.h"
#include "render/object/light/light.h"
#include "render/object/water/water.h"
#include "render/object/water/waterFbo.h"
#include "render/object/water/waterShader.h"

// Water renderer
class WaterRenderer
{
public:

    // DUDV map moving factor changing speed
    static const float DUDV_MOVE_SPEED;

    // Constructor
    WaterRenderer();

    // Render a water terrain
    void render(const Water* water, Light* light[], int lightSize, WaterShader* shader);

    // Bind water quad model
    void bindWater(const Water* water, const WaterFbo* fbo);

    // Unbind water quad model
    void unbindWater();

private:

    // DUDV map moving factor
    float moveFac;

    // Sort light
    void sortLight(Light* light[], int lightSize);
};

#endif
