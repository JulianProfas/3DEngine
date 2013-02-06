#ifndef ENGIE_TERRAIN_H
#define ENGIE_TERRAIN_H

#include <string>
#include "Logger.h"
#include "BMPloader.h"
#include "Renderer.h"
#include "ResourcesManager.h"
#include "Texture.h"

class Terrain
{
public:
	//Constructor for a Terrain object
	Terrain(std::string terrainPath, std::string texturePath, float posX, float posY, float posZ, int scale);
	//Destructor for a Terrain object
	~Terrain();
	//Get the index for the vertex buffer map
	int GetVertexBufferIndex();
	//Get the texture
	Texture* GetTexture();
	//Render a Terrain object
	void RenderTerrain(Renderer* renderer, EntityCamera* camera);
	//Load all resources a Terrain object needs
	void LoadResources(Renderer* renderer, ResourcesManager* resourceManager);

private:	
	//Creates the vertices for a Terrain object
	void FillVertices(Renderer* renderer);
	//The x position of the terrain
	float positionX;
	//The y position of the terrain
	float positionY;
	//The z position of the terrain
	float positionZ;
	//The scaling of the height for the terrain
	int scale;
	//The URL to the texture file
	std::string texturePath;
	//The URL to the heightmap file
	std::string terrainPath;
	//BMPLoader object for reading the heightmap file
	BMPloader* m_BMPLoader;
	//Vertices that resembles the terrain
	ENGIE_VERTEX* terrainVertices;
	//Number of vertices needed to create the terrain
	int numberOfVertices;
	//Texture object for the terrain
	Texture* texture;
	//The index of the vertex buffer map
	int vertexBufferIndex;
};

#endif