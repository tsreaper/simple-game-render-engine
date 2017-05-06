#ifndef TERRAIN_H_
#define TERRAIN_H_

#include "../models/rawModel.h"
#include "../textures/texturePack.h"

// Terrain
class Terrain
{
public:
    
    // Size of a terrain
    static const int SIZE;
    
    // Constructor
    Terrain(int _gridX, int _gridZ, TexturePack* _pack, float minHeight, float maxHeight, const char* heightMapName);
    
    // Destructor
    ~Terrain();
    
    // Get X coordinate
    int getX() const;
    
    // Get Z coordinate
    int getZ() const;
    
    // Get grid-X coordinate
    int getGridX() const;
    
    // Get grid-Z coordinate
    int getGridZ() const;
    
    // Get raw model
    RawModel* getRaw() const;
    
    // Get texture pack
    TexturePack* getTexturePack() const;
    
    // Get the height of a position
    float getHeight(float _x, float _z, bool isWorldCoord) const;
    
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
    RawModel* raw;
    
    // Texture pack
    TexturePack* pack;
    
    // Height of each vertex
    float* heightMap;
    
    // Generate terrain raw model by height map
    RawModel* genRaw(float minHeight, float maxHeight, const char* heightMapName);
};

#endif
