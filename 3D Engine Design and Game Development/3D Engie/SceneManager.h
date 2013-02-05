#ifndef ENGIE_SCENEMANAGER_H
#define ENGIE_SCENEMANAGER_H

#include "Logger.h"
#include "Scene.h"
#include <map>
#include <string>

class SceneManager
{
public:
	//Constructor for a SceneManager object
	SceneManager();
	//Destructor for a SceneManager object
	~SceneManager();
	//Add a scene to the sceneMap
	void AddScene(std::string scenePath);
	//Remove a scene from the sceneMap
	void RemoveScene(std::string scenePath);
	//Removes all scenes from the sceneMap
	void ClearSceneMap();
	//Get a Scene object
	Scene* GetScene(std::string scenePath);

private:
	//Map to hold Scene objects
	std::map<std::string, Scene*>* sceneMap;
};

#endif
