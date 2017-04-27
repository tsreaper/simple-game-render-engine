#ifndef TEXTURE_MODEL_H_
#define TEXTURE_MODEL_H_

#include "rawModel.h"
#include "../textures/modelTexture.h"

class TexturedModel
{
    public:
    
    TexturedModel(RawModel* _raw, ModelTexture* _texture);
    RawModel* getRaw();
    ModelTexture* getTexture();
    
    private:
    
    RawModel* raw;
    ModelTexture* texture;
};

#endif
