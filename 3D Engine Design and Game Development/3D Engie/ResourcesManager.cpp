#include "ResourcesManager.h"

ResourcesManager::ResourcesManager(std::string argTexturePath, std::string argModelPath, LPDIRECT3DDEVICE9 device)
{
	texturePath = argTexturePath;
	modelPath = argModelPath;
	this->device = device;
}

ResourcesManager::~ResourcesManager()
{
}

