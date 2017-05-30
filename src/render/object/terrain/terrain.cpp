#include <cstdlib>
#include <cmath>
#include <iostream>

#include "../../../utils/math/math.h"
#include "../../resource/manager/resourceManager.h"
#include "../../resource/loader/modelLoader.h"
#include "../../../thirdparty/lodepng/lodepng.h"

#include "terrain.h"

using namespace std;

// Size of a terrain
const float Terrain::SIZE = 1024;

// Constructor
Terrain::Terrain(
    const char* _name, int _gridX, int _gridZ, float minHeight, float maxHeight, const char* heightMapName
): gridX(_gridX), gridZ(_gridZ)
{
    // Set the coordinates
    x = gridX * SIZE; z = gridZ * SIZE;

    // Set raw model and textures
    model = genModel(minHeight, maxHeight, ("res/heightMap/" + string(heightMapName) + ".png").c_str());
    texture = ResourceManager::getResource<TerrainTexture>(_name);
}

// Destructor
Terrain::~Terrain()
{
    delete heightMap;
    delete model;
    ResourceManager::deleteResource<TerrainTexture>(texture);
}

// Get X coordinate
float Terrain::getX() const
{
    return x;
}

// Get Z coordinate
float Terrain::getZ() const
{
    return z;
}

// Get grid-X coordinate
int Terrain::getGridX() const
{
    return gridX;
}

// Get grid-Z coordinate
int Terrain::getGridZ() const
{
    return gridZ;
}

// Get raw model
RawModel* Terrain::getModel() const
{
    return model;
}

// Get terrain texture
TerrainTexture* Terrain::getTexture() const
{
    return texture;
}

// Get the height of a position
float Terrain::getHeight(float _x, float _z, bool isWorldCoord) const
{
    if (isWorldCoord)
    {
        _x -= x;
        _z -= z;
    }

    // Make sure x and z are not out of range
    if (_x < 0)
        _x = 0;
    if (_x >= SIZE)
        _x = SIZE - 1e-5;
    if (_z < 0)
        _z = 0;
    if (_z >= SIZE)
        _z = SIZE - 1e-5;

    // Calculate the height
    float len = 1.0 * SIZE / (edgeNum-1);
    int cellX = floor(_x / len), cellZ = floor(_z / len);
    _x = (_x - cellX*len) / len;
    _z = (_z - cellZ*len) / len;

    float y0 = heightMap[cellZ*edgeNum+cellX];
    float y1 = heightMap[cellZ*edgeNum+cellX+1];
    float y2 = heightMap[(cellZ+1)*edgeNum+cellX];
    float y3 = heightMap[(cellZ+1)*edgeNum+cellX+1];
    if (_x + _z <= 1)
        // Position is located at the upper triangle
        return _x*(y1-y0) + _z*(y2-y0) + y0;
    else
        // Position is located at the lower triangle
        return (1-_x)*(y2-y3) + (1-_z)*(y1-y3) + y3;
}

// Get the normal vertex of a position
void Terrain::getNorm(float _x, float _z, float* _norm) const
{
    _norm[0] = getHeight(_x-1, _z, false) - getHeight(_x+1, _z, false);
    _norm[1] = 2;
    _norm[2] = getHeight(_x, _z-1, false) - getHeight(_x, _z+1, false);
    Math::normalize(_norm, 3);
}

// Generate terrain raw model by height map
RawModel* Terrain::genModel(float minHeight, float maxHeight, const char* filename)
{
    unsigned error;
    unsigned char* image;
    unsigned int width, height;

    // Load height map using lodepng
    error = lodepng_decode32_file(&image, &width, &height, filename);
    if (error)
    {
        cerr << "ERROR: [Terrain::genModel] Cannot load height map " + string(filename) + "!" << endl;
        exit(-1);
    }
    else if (width != height)
    {
        cerr << "ERROR: [Terrain::genModel] Height map " + string(filename) + " must be a square!" << endl;
        free(image);
        exit(-1);
    }

    // Calculate height map
    edgeNum = width;
    int count = edgeNum * edgeNum;
    heightMap = new float[count];

    for (int i = 0; i < edgeNum; i++)
        for (int j = 0; j < edgeNum; j++)
            heightMap[i*edgeNum+j] = image[(i*edgeNum+j)<<2] / 255.0 * (maxHeight - minHeight) + minHeight;
    free(image);

    // Generate raw model
    float* vert = new float[count*3];
    float* text = new float[count*2];
    float* norm = new float[count*3];
    int* indicies = new int[(edgeNum-1)*(edgeNum-1)*6];

    int ptr = 0;
    for (int i = 0; i < edgeNum; i++)
        for (int j = 0; j < edgeNum; j++)
        {
            float _x = 1.0 * j / (edgeNum-1) * SIZE;
            float _z = 1.0 * i / (edgeNum-1) * SIZE;
            vert[ptr*3] = _x;
            vert[ptr*3+1] = getHeight(_x, _z, false);
            vert[ptr*3+2] = _z;
            text[ptr*2] = _x/SIZE;
            text[ptr*2+1] = _z/SIZE;

            float _norm[3];
            getNorm(_x, _z, _norm);
            norm[ptr*3] = _norm[0];
            norm[ptr*3+1] = _norm[1];
            norm[ptr*3+2] = _norm[2];

            ptr++;
        }

    ptr = 0;
    for (int i = 0; i < edgeNum-1; i++)
        for (int j = 0; j < edgeNum-1; j++)
        {
            int idx0 = i*edgeNum + j;
            int idx1 = idx0 + 1;
            int idx2 = idx0 + edgeNum;
            int idx3 = idx1 + edgeNum;
            indicies[ptr++] = idx0;
            indicies[ptr++] = idx2;
            indicies[ptr++] = idx1;
            indicies[ptr++] = idx1;
            indicies[ptr++] = idx2;
            indicies[ptr++] = idx3;
        }

    RawModel* raw = ModelLoader::loadRawModel("terrain", vert, count*3, text, count*2, norm, count*3, indicies, ptr);
    return raw;
}
