#include "ResourcesManager.h"

ResourcesManager::ResourcesManager(LPDIRECT3DDEVICE9 g_pd3dDevice)
{
	device = g_pd3dDevice;
}

ResourcesManager::~ResourcesManager()
{
}

Model& ResourcesManager::LoadModel(std::string filePath)
{
	std::map<std::string, Model*>::iterator it;
	it = modelMap.find(filePath);
	
	if(it != modelMap.end())
	{
		if(it->first.compare(filePath) == 0)
		{
			Logger::GetInstance()->Write("Model al ingeladen");
			return *it->second;
		}
	}

	Model* m = new Model(device, filePath);

	typedef std::pair<std::string, Model*> pair;
	modelMap.insert(pair(filePath, m));

	return *m;
}

Texture& ResourcesManager::LoadTexture(std::string filePath)
{
	std::map<std::string, Texture*>::iterator it;
	it = textureMap.find(filePath);

	if(it != textureMap.end())
	{
		if(it->first.compare(filePath) == 0)
		{
			Logger::GetInstance()->Write("Texture al ingeladen");
			return *it->second;
		}
	}

	Texture* t = new Texture(device, filePath);

	typedef std::pair<std::string, Texture*> pair;
	textureMap.insert(pair(filePath, t));

	return *t;
}