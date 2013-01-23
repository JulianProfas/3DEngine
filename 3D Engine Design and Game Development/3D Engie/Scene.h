#ifndef ENGIE_SCENE_H
#define ENGIE_SCENE_H

#include <string>
#include "Terrain.h"
#include "Renderer.h"
#include "EntityModel.h"
#include "ResourcesManager.h"
#include <list>
//#include "SkyBox.h"
//#include "EntityCamera.h"
#include <fstream>
#include <iostream>

typedef std::list<EntityModel> EntityList;

class Scene
{
public:
	Scene(Renderer* r, ResourcesManager* rm, std::string sceneName);
	~Scene();
	void LoadScene(std::string sceneName);
	void RenderScene(HWND hWnd);
private:
	Terrain* sceneTerrain;
	Renderer* sceneRenderer;
	EntityList* sceneEntitys;
	//EntityCamera sceneCamera;
	//SkyBox sceneSky;
	std::string sceneName;
	ResourcesManager* resourceManager;
};

#endif