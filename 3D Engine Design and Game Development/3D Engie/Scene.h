#ifndef ENGIE_SCENE_H
#define ENGIE_SCENE_H

#include <string>
#include "Terrain.h"
#include "Renderer.h"
#include "EntityModel.h"
#include <list>
//#include "SkyBox.h"
//#include "EntityCamera.h"
#include <fstream>
#include <iostream>

class Scene
{
public:
	Scene();
	~Scene();
	void LoadScene(std::string sceneName);
	void RenderScene();
private:
	Terrain* sceneTerrain;
	Renderer* sceneRenderer;
	std::list<EntityModel> sceneEntitys;
	//EntityCamera sceneCamera;
	//SkyBox sceneSky;
	std::string sceneName;
};

#endif