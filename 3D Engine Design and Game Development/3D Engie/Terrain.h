#ifndef ENGIE_TERRAIN_H
#define ENGIE_TERRAIN_H

#include <string>
#include "Logger.h"
#include "BMPloader.h"
#include "Renderer.h"
#include "ResourcesManager.h"
#include "Texture.h"
#include "EntityCamera.h"

class Terrain
{
public:
	Terrain(std::string terrainPath, std::string texturePath);
	~Terrain();

	int GetVertexBufferIndex();
	int GetNumberOfVertices();
	Texture* GetTexture();
	void RenderTerrain(Renderer* renderer, EntityCamera* camera);
	void SetPositionX(float x);
	void SetPositionY(float y);
	void SetPositionZ(float z);
	void LoadResources(Renderer* renderer, ResourcesManager* resourceManager);

private:	
	void FillVertices(Renderer* renderer);
	float posX;
	float posY;
	float posZ;
	std::string texturePath;
	std::string terrainPath;
	BMPloader* m_BMPLoader;
	ENGIE_VERTEX* terrainVertices;
	int numberOfVertices;
	Texture* texture;
	int vertexBufferIndex;
};

#endif