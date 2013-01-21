#ifndef ENGIE_SCENEMANAGER_H
#define ENGIE_SCENEMANAGER_H

#include "Logger.h"
#include "Scene.h"
#include <map>
#include <string>

typedef std::map<std::string, Scene*> SceneMap;

class SceneManager
{
public:
	SceneManager();
	~SceneManager();
	void AddScene(std::string sceneName);
	void RemoveScene(std::string sceneName);
	void ClearSceneMap();
	SceneMap* GetSceneMap();
	Scene* GetScene(std::string sceneName);
private:
	SceneMap* scenes;
};

#endif
