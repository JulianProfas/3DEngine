#ifndef ENGIE_SKYBOX_H
#define ENGIE_SKYBOX_H

#include <vector>
#include "Renderer.h"
#include "windows.h"
#include "Logger.h"
#include "Texture.h"
#include "EntityCamera.h"
#include "ResourcesManager.h"

class SkyBox
{
public:
	//Constructor for a SkyBox object
	SkyBox(std::string texturePath [6]);
	//Destructor for a SkyBox object
	~SkyBox();
	//Renders the SkyBox
	void Render(Renderer* renderer, EntityCamera* camera);
	//Loads all resources need for a Skybox object, including creating the vertices and vertex buffer
	void LoadResources(Renderer* renderer, ResourcesManager* resourceManager);

private:	
	//Creates the vertices and vertex buffer which resembles the SkyBox
	void FillVertices(Renderer* renderer);
	//Index for the vertex buffer map
	int	vertexBufferIndex;
	//Number of vertices needed to create the SkyBox
	int	numberOfVertices;
	//Texture array to hold 6 textures
	Texture* texture[6];
	//String array to hold 6 URL to texturefiles
	std::string texturePath[6];  
};

#endif