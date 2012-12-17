#include <string>
#include <list>
#include "Model.h"
#include "Texture.h"

class ResourcesManager
{
public:
	ResourcesManager(std::string texturePath, std::string modelPath);
	~ResourcesManager();
	void LoadModel(std::string name);
	void LoadTexture(std::string name);
	void SetModelPath(std::string argModelPath);
	void SetTexturePath(std::string argTexturePath);
private:
	std::string modelPath;
	std::string texturePath;
	std::list<Model*> modelList;
	std::list<Texture*> textureList;
};