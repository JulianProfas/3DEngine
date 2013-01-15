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

	LPDIRECT3DVERTEXBUFFER9 GetVertexBuffer();
	int GetNumberOfVertices();
	Texture* GetTexture();
private:	
	void FillVertices(Renderer* renderer);
	BMPloader* m_BMPLoader;

	ENGIE_VERTEX* vertices;
	int numberOfVertices;
	Texture* texture;
	LPDIRECT3DVERTEXBUFFER9 VB;
};

#endif