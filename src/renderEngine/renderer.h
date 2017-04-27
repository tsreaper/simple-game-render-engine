#ifndef RENDERER_H_
#define RENDERER_H_

#include "rawModel.h"

class Renderer
{
    public:
    
    void prepare();
    void render(RawModel& model);
};

#endif
