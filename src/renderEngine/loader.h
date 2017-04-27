#ifndef LOADER_H_
#define LOADER_H_

#include <vector>
#include "../glew.h"
#include "rawModel.h"

using namespace std;

class Loader
{
    public:
    
    RawModel loadToVao(float* positions, int positionSize, int* indicies, int indiciesSize);
    void cleanUp();
    
    private:
    
    vector<GLuint> vaos, vbos;
    
    int createVao();
    void storeDataInAttrList(int attrNumber, float* data, int size);
    void unbindVao();
    void bindIndiciesBuffer(int* indicies, int size);
};

#endif
