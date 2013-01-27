#ifndef ENGIE_SKYBOX_H
#define ENGIE_SKYBOX_H

#include <vector>
#include "Renderer.h"
#include "windows.h"
#include "Logger.h"
#include "Texture.h"
#include "EntityCamera.h"
	
typedef std::vector<Texture*> SkyTexture;

class SkyBox
{
public:
	SkyBox(Renderer *renderer, SkyTexture textures);
	~SkyBox();
	void Render(Renderer* renderer, EntityCamera* camera);
private:	
	void FillVertices(Renderer* renderer);
	int	vertexBufferIndex;
	int	numberOfVertices;
	SkyTexture textures;
};

#endif