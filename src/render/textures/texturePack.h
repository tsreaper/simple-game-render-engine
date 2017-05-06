#ifndef TEXTURE_PACK_H
#define TEXTURE_PACK_H

#include <string>
#include "modelTexture.h"

using namespace std;

// A pack of texture. Used for multitexturing a terrain
class TexturePack
{
public:
    
    // Constructor
    TexturePack(const char* _name, ModelTexture* _k, ModelTexture* _r, ModelTexture* _g, ModelTexture* _b, ModelTexture* _blend);
    
    // Destructor
    ~TexturePack();
    
    // Get name of texture pack
    const char* getName() const;
    
    // Get black texture
    ModelTexture* getK() const;
    
    // Get red texture
    ModelTexture* getR() const;
    
    // Get green texture
    ModelTexture* getG() const;
    
    // Get blue texture
    ModelTexture* getB() const;
    
    // Get blend map
    ModelTexture* getBlend() const;
    
private:
    
    // Name of texture pack
    string name;
    
    // Textures
    ModelTexture* k;
    ModelTexture* r;
    ModelTexture* g;
    ModelTexture* b;
    
    // Blend map
    ModelTexture* blend;
};

#endif
