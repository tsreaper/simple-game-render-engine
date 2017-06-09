#ifndef _MODEL_LOADER_H
#define _MODEL_LOADER_H

#include <vector>
#include "glew.h"
#include "render/resource/model/rawModel.h"

using namespace std;

// Model information Loader
class ModelLoader
{
public:

    // Create VAO and load a raw model
    static RawModel* loadRawModel(const char* name, const float* positions, int positionSize, const float* textureCoords, int textureCoordSize, const float* norms, int normSize, const int* indicies, int indiciesSize);

    // Create VAO and load vertices only
    static RawModel* loadVertices(const char* name, const float* positions, int positionSize);

private:

    // Create a VAO
    static GLuint createVao();

    // Create a VBO of index data
    static GLuint bindIndiciesBuffer(const int* indicies, int size);

    // Create a VBO of vertex data and store it into VAO
    static GLuint storeDataInAttrList(int attrNumber, int dimension, const float* data, int size);

    // Unbind current VAO
    static void unbindVao();
};

#endif
