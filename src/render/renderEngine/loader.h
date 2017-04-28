#ifndef LOADER_H_
#define LOADER_H_

#include <vector>
#include "../../glew.h"
#include "../models/rawModel.h"

using namespace std;

// Model information Loader
class Loader
{
public:
    
    // Load vertex position and texture coordinate of a model into VAO
    static RawModel* loadToVao(const float* positions, int positionSize, const float* textureCoords, int textureCoordSize, const int* indicies, int indiciesSize);
    
    // Create texture from file
    static int loadTexture(const char* filename);
    
    // Clean up VAOs, VBOs and textures
    static void cleanUp();
    
private:
    
    // VAO, VBO and texture lists. Used for clean up
    static vector<GLuint> vaos, vbos, textures;
    
    // Create a VAO
    static int createVao();
    
    // Create a VBO of vertex data and store it into VAO
    static void storeDataInAttrList(int attrNumber, int dimension, const float* data, int size);
    
    // Unbind current VAO
    static void unbindVao();
    
    // Create a VBO of index data
    static void bindIndiciesBuffer(const int* indicies, int size);
};

#endif
