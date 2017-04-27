#ifndef RENDERER_H_
#define RENDERER_H_

#include "../models/texturedModel.h"

class Renderer
{
    public:
    
    void prepare();
    void render(TexturedModel* model);
};

#endif
