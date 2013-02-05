#include "SceneManager.h"

/*
	Constructor
*/
SceneManager::SceneManager()
{
	this->sceneMap = new std::map<std::string, Scene*>();
	Logger::GetInstance()->Write("SceneManager created");
}

/*
	Destructor
*/
SceneManager::~SceneManager()
{
	this->ClearSceneMap();
	Logger::GetInstance()->Write("SceneManager destroyed");
}

/*
	Add a new scene to the SceneMap
*/
void SceneManager::AddScene(std::string scenePath)
{
	Scene* s = new Scene(scenePath);
	Logger::GetInstance()->Write("Scene " + scenePath + " created");
	this->sceneMap->insert(std::pair<std::string, Scene*>(scenePath, s));
	Logger::GetInstance()->Write("Scene " + scenePath + " added to SceneMap");
}

/*
	Remove a scene from the SceneMap: the destructor is called from the removed scene.
*/
void SceneManager::RemoveScene(std::string scenePath)
{
	this->sceneMap->erase(scenePath);
}

/*
	All the scenes in the SceneMap are dropped: their destructors are called, 
	and then they are removed from the SceneMap, leaving it with a size of 0.
*/
void SceneManager::ClearSceneMap()
{
	this->sceneMap->clear();
}

/*
	Returns a scene by sceneName
*/
Scene* SceneManager::GetScene(std::string scenePath)
{
	return this->sceneMap->find(scenePath)->second;
}