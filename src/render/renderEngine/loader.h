#ifndef LOADER_H_
#define LOADER_H_

#include <vector>
#include "../../glew.h"
#include "../models/rawModel.h"
#include "../textures/modelTexture.h"

using namespace std;

// Model information Loader
class Loader
{
public:
    
    // Create VAO and load a raw model
    static RawModel* loadRawModel(const char* name, const float* positions, int positionSize, const float* textureCoords, int textureCoordSize, const float* norms, int normSize, const int* indicies, int indiciesSize);
    
    // Create texture from file
    static ModelTexture* loadTexture(const char* filename);
    
private:
    
    // Create a VAO
    static int createVao();
    
    // Create a VBO of index data
    static int bindIndiciesBuffer(const int* indicies, int size);
    
    // Create a VBO of vertex data and store it into VAO
    static int storeDataInAttrList(int attrNumber, int dimension, const float* data, int size);
    
    // Unbind current VAO
    static void unbindVao();
};

#endif
