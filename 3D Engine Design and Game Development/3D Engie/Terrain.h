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
	Terrain(std::string terrainFileName, std::string texturefilename, Renderer* renderer, ResourcesManager* resourceManager);
	~Terrain();

	int GetVertexBufferIndex();
	int GetNumberOfVertices();
	Texture* GetTexture();
	void RenderTerrain(Renderer* r);
	void SetPositionX(float x);
	void SetPositionY(float y);
	void SetPositionZ(float z);
	void Move(int d, float unit);
private:	
	void FillVertices(Renderer* renderer);
	float posX;
	float posY;
	float posZ;
	BMPloader* m_BMPLoader;
	ENGIE_VERTEX* terrainVertices;
	int numberOfVertices;
	Texture* terrainTexture;
	int vertexBufferIndex;
};

#endif