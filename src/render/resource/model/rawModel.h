#ifndef _RAW_MODEL_H
#define _RAW_MODEL_H

#include <string>
#include "glew.h"

using namespace std;

// Model without texture
class RawModel
{
public:

    // Constructor
    RawModel(const char* _name, GLuint _vaoId, GLuint _vertexCount, int _vboCount = 4);

    // Destructor
    ~RawModel();

    // Get raw model name
    const char* getName() const;

    // Get VAO id
    GLuint getVaoId() const;

    // Get number of vertex
    int getVertexCount() const;

    // Add a VBO id into list
    void addVboId(int pos, GLuint id);

private:

    // Raw model name
    string name;

    // VAO id
    GLuint vaoId;

    // Number of vertex
    int vertexCount;

    // VBO ids
    GLuint* vboIds;

    // Number of VBOs
    int vboCount;
};

#endif
