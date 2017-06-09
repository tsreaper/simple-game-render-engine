#include <iostream>
#include "thirdparty/lodepng/lodepng.h"

#include "render/resource/loader/modelLoader.h"

using namespace std;

// Create VAO and load a raw model
RawModel* ModelLoader::loadRawModel(const char* name, const float* positions, int positionSize, const float* textureCoords, int textureCoordSize, const float* norms, int normSize, const int* indicies, int indiciesSize)
{
    // Create raw model
    GLuint vaoId = createVao();
    RawModel* raw = new RawModel(name, vaoId, indiciesSize);

    // Bind VBO
    raw->addVboId(0, bindIndiciesBuffer(indicies, indiciesSize));
    raw->addVboId(1, storeDataInAttrList(0, 3, positions, positionSize));
    raw->addVboId(2, storeDataInAttrList(1, 2, textureCoords, textureCoordSize));
    raw->addVboId(3, storeDataInAttrList(2, 3, norms, normSize));

    unbindVao();
    return raw;
}

// Create VAO and load vertices only
RawModel* ModelLoader::loadVertices(const char* name, const float* positions, int positionSize)
{
    // Create raw model
    GLuint vaoId = createVao();
    RawModel* raw = new RawModel(name, vaoId, positionSize/3, 1);

    // Bind VBO
    raw->addVboId(0, storeDataInAttrList(0, 3, positions, positionSize));

    unbindVao();
    return raw;
}

// Create a VAO
GLuint ModelLoader::createVao()
{
    GLuint arrays[1];
    glGenVertexArrays(1, arrays);
    glBindVertexArray(arrays[0]);
    return arrays[0];
}

// Create a VBO of index data
GLuint ModelLoader::bindIndiciesBuffer(const int* indicies, int size)
{
    GLuint buffers[1];
    glGenBuffers(1, buffers);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size*sizeof(int), indicies, GL_STATIC_DRAW);
    return buffers[0];
}

// Create a VBO of vertex data and store it into VAO
GLuint ModelLoader::storeDataInAttrList(int attrNumber, int dimension, const float* data, int size)
{
    GLuint buffers[1];
    glGenBuffers(1, buffers);
    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
    glBufferData(GL_ARRAY_BUFFER, size*sizeof(float), data, GL_STATIC_DRAW);
    glVertexAttribPointer(attrNumber, dimension, GL_FLOAT, false, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    return buffers[0];
}

// Unbind current VAO
void ModelLoader::unbindVao()
{
    glBindVertexArray(0);
}
