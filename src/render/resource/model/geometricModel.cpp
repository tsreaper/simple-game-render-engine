#include <cstdlib>
#include <iostream>

#include "render/resource/loader/modelLoader.h"
#include "render/resource/model/geometricModel.h"

using namespace std;

// Geometric model IDs
int GeometricModel::CUBE = 0;
int GeometricModel::SQUARE_XZ = 1;

// Geometric models
RawModel* GeometricModel::cubeModel = NULL;
RawModel* GeometricModel::squareXzModel = NULL;

// Get specific geometric model
RawModel* GeometricModel::getGeometricModel(int modelId)
{
    if (modelId == CUBE)
    {
        if (cubeModel == NULL)
            cubeModel = createCube();
        return cubeModel;
    }
    else if (modelId == SQUARE_XZ)
    {
        if (squareXzModel == NULL)
            squareXzModel = createSquareXz();
        return squareXzModel;
    }
    else
    {
        cerr << "ERROR: [GeometricModel::getGeometricModel] No such model " << modelId << "!" << endl;
        exit(-1);
    }
}

// Clean up the models
void GeometricModel::cleanUp()
{
    delete cubeModel;
}

// Generate a unit cube model
RawModel* GeometricModel::createCube()
{
    float vertices[] = {
        -1, 1, -1,
        -1, -1, -1,
        1, -1, -1,
        1, -1, -1,
        1, 1, -1,
        -1, 1, -1,

        -1, -1, 1,
        -1, -1, -1,
        -1, 1, -1,
        -1, 1, -1,
        -1, 1, 1,
        -1, -1, 1,

        1, -1, -1,
        1, -1, 1,
        1, 1, 1,
        1, 1, 1,
        1, 1, -1,
        1, -1, -1,

        -1, -1, 1,
        -1, 1, 1,
        1, 1, 1,
        1, 1, 1,
        1, -1, 1,
        -1, -1, 1,

        -1, 1, -1,
        1, 1, -1,
        1, 1, 1,
        1, 1, 1,
        -1, 1, 1,
        -1, 1, -1,

        -1, -1, -1,
        -1, -1, 1,
        1, -1, -1,
        1, -1, -1,
        -1, -1, 1,
        1, -1, 1
    };

    return ModelLoader::loadVertices("cube", vertices, 108);
}


// Generate a square on the XZ plane
RawModel* GeometricModel::createSquareXz()
{
    float vertices[] = {
        0, 0, 0,
        0, 0, 1,
        1, 0, 0,
        1, 0, 1
    };

    return ModelLoader::loadVertices("squareXz", vertices, 12);
}
