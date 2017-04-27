#include "loader.h"

using namespace std;

RawModel Loader::loadToVao(float* positions, int positionSize, int* indicies, int indiciesSize)
{
    int vaoId = createVao();
    bindIndiciesBuffer(indicies, indiciesSize);
    storeDataInAttrList(0, positions, positionSize);
    unbindVao();
    return RawModel(vaoId, indiciesSize);
}

void Loader::cleanUp()
{
    glDeleteVertexArrays(vaos.size(), &(*vaos.begin()));
    glDeleteBuffers(vbos.size(), &(*vbos.begin()));
}

int Loader::createVao()
{
    GLuint arrays[1];
    glGenVertexArrays(1, arrays);
    vaos.push_back(arrays[0]);
    glBindVertexArray(arrays[0]);
    return arrays[0];
}

void Loader::storeDataInAttrList(int attrNumber, float* data, int size)
{
    GLuint buffers[1];
    glGenBuffers(1, buffers);
    vbos.push_back(buffers[0]);
    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
    glBufferData(GL_ARRAY_BUFFER, size*sizeof(float), data, GL_STATIC_DRAW);
    glVertexAttribPointer(attrNumber, 3, GL_FLOAT, false, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Loader::unbindVao()
{
    glBindVertexArray(0);
}

void Loader::bindIndiciesBuffer(int* indicies, int size)
{
    GLuint buffers[1];
    glGenBuffers(1, buffers);
    vbos.push_back(buffers[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size*sizeof(int), indicies, GL_STATIC_DRAW);
}
