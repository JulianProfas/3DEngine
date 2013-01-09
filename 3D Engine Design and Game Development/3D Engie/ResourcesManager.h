#include <string>
#include <map>
#include <d3dx9.h>
#include "Model.h"
#include "Texture.h"


class ResourcesManager
{
public:
	ResourcesManager(LPDIRECT3DDEVICE9 g_pd3dDevice);
	~ResourcesManager();
	Model& LoadModel(std::string filePath);
	Texture& LoadTexture(std::string filePath);
private:
	std::map<std::string, Model*> modelMap ;
	std::map<std::string, Texture*> textureMap;
	LPDIRECT3DDEVICE9 device;
};