#ifndef ENGIE_RESOURCEMANAGER_H
#define ENGIE_RESOURCEMANAGER_H

#include <string>
#include <map>
#include <d3dx9.h>
#include "Model.h"
#include "Texture.h"

class ResourcesManager
{
public:
	//Constructor for a ResourcesManager object
	ResourcesManager();
	//Destructor for a ResourcesManager object
	~ResourcesManager();
	//Load a model from the given filepath
	Model* LoadModel(LPDIRECT3DDEVICE9 device, std::string filePath);
	//Load a texture from the given filepath
	Texture* LoadTexture(LPDIRECT3DDEVICE9 device, std::string filePath);
	//Remove a model from the modelMap
	void RemoveModel(std::string modelName);
	//Remove a texture from the textureMap
	void RemoveTexture(std::string textureName);
	//Removes all models from the modelMap
	void ClearModelMap();
	//Removes all textures from the textureMap
	void ClearTextureMap();

private:
	//Cleares both the textureMap and modelMap
	void CleanUp();

	//Map to hold all models
	std::map<std::string, Model*> modelMap;
	//Map to hold all textures
	std::map<std::string, Texture*> textureMap;
};

#endif