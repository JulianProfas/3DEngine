#include "SceneManager.h"

/*
	Constructor
*/
SceneManager::SceneManager()
{
	this->scenes = new SceneMap();
	Logger::GetInstance()->Write("SceneManager aangemaakt");
}

/*
	Destructor
*/
SceneManager::~SceneManager()
{
	this->ClearSceneMap();
	Logger::GetInstance()->Write("SceneManager verwijderd");
}

/*
	Add a new scene to the SceneMap
*/
void SceneManager::AddScene(std::string sceneName)
{
	//Scene* s = new Scene();
	Logger::GetInstance()->Write("Scene " + sceneName + " aangemaakt");
	//this->scenes->insert(std::pair<std::string, Scene*>(sceneName, s));
	Logger::GetInstance()->Write("Scene " + sceneName + " toegevoegd aan SceneMap");
}

/*
	Remove a scene from the SceneMap: the destructor is called from the removed scene.
*/
void SceneManager::RemoveScene(std::string sceneName)
{
	this->scenes->erase(sceneName);

}

/*
	All the scenes in the SceneMap are dropped: their destructors are called, 
	and then they are removed from the SceneMap, leaving it with a size of 0.
*/
void SceneManager::ClearSceneMap()
{
	this->scenes->clear();
}

/*
	Returns the SceneMap
*/
SceneMap* SceneManager::GetSceneMap()
{
	return this->scenes;
}

/*
	Returns a scene by sceneName
*/
Scene* SceneManager::GetScene(std::string sceneName)
{
	return this->scenes->find(sceneName)->second;
}