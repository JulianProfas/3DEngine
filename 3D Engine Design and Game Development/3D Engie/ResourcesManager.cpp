#include "ResourcesManager.h"

/*
	Constructor for a ResourcesManager object
*/
ResourcesManager::ResourcesManager()
{

}

/*
	Destructor for a ResourcesManager object
*/
ResourcesManager::~ResourcesManager()
{
	this->CleanUp();
}

/*
	Load a model from the given filepath
	@param device, it requires a device to load a model
	@param filePath, the URL to the modelfile
	@return Model*, returns an already loaded Model or a newly created Model 
*/
Model* ResourcesManager::LoadModel(LPDIRECT3DDEVICE9 device, std::string filePath)
{
	//Check if the model is already in the modelMap(Loaded), if not make a new Model
	Model* m = this->modelMap.find(filePath)->second;
	if(NULL != m)
	{
		Logger::GetInstance()->Write("Model: " + filePath + " already loaded");
		return m;
	}
	else
	{
		m = new Model(device, filePath);
	}

	//Insert the Model in the modelMap 
	this->modelMap.insert(std::pair<std::string, Model*>(filePath, m));

	return m;
}

/*
	Load a texture from the given filepath
	@param device, it requires a device to load a texture
	@param filePath, the URL to the texturefile
	@return Texture*, returns an already loaded Texture or a newly created Texture
*/
Texture* ResourcesManager::LoadTexture(LPDIRECT3DDEVICE9 device, std::string filePath)
{
	//Check if the Texture is already in the textureMap(Loaded), if not make a new Texture
	Texture* t = this->textureMap.find(filePath)->second; 
	if(NULL != t)
	{
		Logger::GetInstance()->Write("Texture: " + filePath + " already loaded");
		return t;
	}
	else
	{
		t = new Texture(device, filePath);
	}

	//Insert the Texture in the textureMap 
	this->textureMap.insert(std::pair<std::string, Texture*>(filePath, t));

	return t;
}

/*
	Remove a model from the modelMap
	@param filePath, the URL to the modelfile
*/
void ResourcesManager::RemoveModel(std::string filePath)
{
	this->modelMap.erase(filePath);
}

/*
	Remove a Texture from the textureMap
	@param filePath, the URL to the texturefile
*/
void ResourcesManager::RemoveModel(std::string filePath)
{
	this->textureMap.erase(filePath);
}

/*
	Removes all models from the modelMap
*/
void ResourcesManager::ClearModelMap()
{
	this->modelMap.clear();
}

/*
	Removes all textures from the texturesMap
*/
void ResourcesManager::ClearTextureMap()
{
	this->textureMap.clear();
}

/*
	Cleares both the textureMap and modelMap
*/
void ResourcesManager::CleanUp()
{
	this->ClearModelMap();
	this->ClearTextureMap();
}