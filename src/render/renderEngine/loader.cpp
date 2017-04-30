#include <iostream>
#include "../../thirdparty/lodepng.h"
#include "loader.h"

using namespace std;

// Create VAO and load a raw model
RawModel* Loader::loadRawModel(const char* name, const float* positions, int positionSize, const float* textureCoords, int textureCoordSize, const float* norms, int normSize, const int* indicies, int indiciesSize)
{
    // Create raw model
    int vaoId = createVao();
    RawModel* raw = new RawModel(name, vaoId, indiciesSize);
    
    // Bind VBO
    raw->addVboId(0, bindIndiciesBuffer(indicies, indiciesSize));
    raw->addVboId(1, storeDataInAttrList(0, 3, positions, positionSize));
    raw->addVboId(2, storeDataInAttrList(1, 2, textureCoords, textureCoordSize));
    raw->addVboId(3, storeDataInAttrList(2, 3, norms, normSize));
    
    unbindVao();
    return raw;
}

// Create texture from file
ModelTexture* Loader::loadTexture(const char* filename)
{
    unsigned error;
    unsigned char* image;
    unsigned int width, height;
    
    // Load image using lodepng
    error = lodepng_decode32_file(&image, &width, &height, ("res/" + string(filename)).c_str());
    if (error)
        cerr << "ERROR: [Loader] PNG decoder error " << error << " - " << lodepng_error_text(error) << endl;
    
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
    
    free(image);
    return new ModelTexture(filename, texId[0]);
}

// Create a VAO
int Loader::createVao()
{
    GLuint arrays[1];
    glGenVertexArrays(1, arrays);
    glBindVertexArray(arrays[0]);
    return arrays[0];
}

// Create a VBO of index data
int Loader::bindIndiciesBuffer(const int* indicies, int size)
{
    GLuint buffers[1];
    glGenBuffers(1, buffers);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size*sizeof(int), indicies, GL_STATIC_DRAW);
    return buffers[0];
}

// Create a VBO of vertex data and store it into VAO
int Loader::storeDataInAttrList(int attrNumber, int dimension, const float* data, int size)
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
void Loader::unbindVao()
{
    glBindVertexArray(0);
}
