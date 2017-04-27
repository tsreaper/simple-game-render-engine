#ifndef LOADER_H_
#define LOADER_H_

#include <vector>
#include "../glew.h"
#include "../models/rawModel.h"

using namespace std;

class Loader
{
    public:
    
    RawModel loadToVao(float* positions, int positionSize, float* textureCoords, int textureCoordSize, int* indicies, int indiciesSize);
    int loadTexture(char* filename);
    void cleanUp();
    
    private:
    
    vector<GLuint> vaos, vbos, textures;
    
    int createVao();
    void storeDataInAttrList(int attrNumber, int dimension, float* data, int size);
    void unbindVao();
    void bindIndiciesBuffer(int* indicies, int size);
};

#endif
