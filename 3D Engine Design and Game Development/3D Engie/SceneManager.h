#ifndef ENGIE_SCENEMANAGER_H
#define ENGIE_SCENEMANAGER_H

#include "Logger.h"
#include "Scene.h"
#include <map>
#include <string>

class SceneManager
{
public:
	SceneManager(ResourcesManager* resourceManager, Renderer* renderer);
	~SceneManager();
	void AddScene(std::string sceneName);
	void RemoveScene(std::string sceneName);
	void ClearSceneMap();
	std::map<std::string, Scene*>* GetSceneMap();
	Scene* GetScene(std::string sceneName);
private:
	std::map<std::string, Scene*>* scenes;
	ResourcesManager* resourceManager;
	Renderer* renderer;
};

#endif
