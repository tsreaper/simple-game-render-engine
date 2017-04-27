#include <iostream>
#include "../thirdparty/lodepng.h"
#include "loader.h"

using namespace std;

RawModel Loader::loadToVao(float* positions, int positionSize, float* textureCoords, int textureCoordSize, int* indicies, int indiciesSize)
{
    int vaoId = createVao();
    bindIndiciesBuffer(indicies, indiciesSize);
    storeDataInAttrList(0, 3, positions, positionSize);
    storeDataInAttrList(1, 2, textureCoords, textureCoordSize);
    unbindVao();
    return RawModel(vaoId, indiciesSize);
}

int Loader::loadTexture(char* filename)
{
    unsigned error;
    unsigned char* image;
    unsigned int width, height;
    
    // Load image using lodepng
    error = lodepng_decode32_file(&image, &width, &height, filename);
    if (error)
        cerr << "ERROR: PNG decoder error " << error << "- " << lodepng_error_text(error) << endl;
    
    // Generate texture
    GLuint texId[1];
    glGenTextures(1, texId);
    glBindTexture(GL_TEXTURE_2D, texId[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    textures.push_back(texId[0]);
    free(image);
    return texId[0];
}

void Loader::cleanUp()
{
    glDeleteVertexArrays(vaos.size(), &(*vaos.begin()));
    glDeleteBuffers(vbos.size(), &(*vbos.begin()));
    glDeleteTextures(textures.size(), &(*textures.begin()));
}

int Loader::createVao()
{
    GLuint arrays[1];
    glGenVertexArrays(1, arrays);
    vaos.push_back(arrays[0]);
    glBindVertexArray(arrays[0]);
    return arrays[0];
}

void Loader::storeDataInAttrList(int attrNumber, int dimension, float* data, int size)
{
    GLuint buffers[1];
    glGenBuffers(1, buffers);
    vbos.push_back(buffers[0]);
    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
    glBufferData(GL_ARRAY_BUFFER, size*sizeof(float), data, GL_STATIC_DRAW);
    glVertexAttribPointer(attrNumber, dimension, GL_FLOAT, false, 0, 0);
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
