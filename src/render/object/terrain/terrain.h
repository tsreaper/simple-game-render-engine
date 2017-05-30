#ifndef _TERRAIN_H
#define _TERRAIN_H

#include <string>
#include "../../resource/model/rawModel.h"
#include "../../resource/texture/terrainTexture.h"

using namespace std;

// Terrain
class Terrain
{
public:

    // Size of a terrain
    static const float SIZE;

    // Constructor
    Terrain(const char* _name, int _gridX, int _gridZ, float minHeight, float maxHeight, const char* heightMapName);

    // Destructor
    ~Terrain();

    // Get X coordinate
    float getX() const;

    // Get Z coordinate
    float getZ() const;

    // Get grid-X coordinate
    int getGridX() const;

    // Get grid-Z coordinate
    int getGridZ() const;

    // Get raw model
    RawModel* getModel() const;

    // Get terrain texture
    TerrainTexture* getTexture() const;

    // Get the height of a position
    float getHeight(float _x, float _z, bool isWorldCoord = true) const;

    // Get the normal vertex of a position
    void getNorm(float _x, float _z, float* _norm) const;

private:

    // Coordinates in the world
    float x, z;

    // Grod coordinates of the terrain
    int gridX, gridZ;

    // Number of vertices on an edge
    int edgeNum;

    // Raw model
    RawModel* model;

    // Texture pack
    TerrainTexture* texture;

    // Height of each vertex
    float* heightMap;

    // Generate terrain raw model by height map
    RawModel* genModel(float minHeight, float maxHeight, const char* filename);
};

#endif
