#include <string>
#include <set>
#include <d3dx9.h>
#include "Model.h"
#include "Texture.h"


class ResourcesManager
{
public:
	ResourcesManager(std::string texturePath, std::string modelPath, LPDIRECT3DDEVICE9 device);
	~ResourcesManager();
	void LoadModel(std::string name);
	void LoadTexture(std::string name, LPDIRECT3DDEVICE9 device);
	void SetModelPath(std::string argModelPath);
	void SetTexturePath(std::string argTexturePath);
private:
	std::string modelPath;
	std::string texturePath;
	std::set<Model*> modelList;
	std::set<Texture*> textureList;
	LPDIRECT3DDEVICE9 device;
};