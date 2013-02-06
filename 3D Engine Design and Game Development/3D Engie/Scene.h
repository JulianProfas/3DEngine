#ifndef ENGIE_SCENE_H
#define ENGIE_SCENE_H

#include <string>
#include "Terrain.h"
#include "Renderer.h"
#include "EntityModel.h"
#include "ResourcesManager.h"
#include <list>
#include "SkyBox.h"
#include "EntityCamera.h"
#include <fstream>
#include <iostream>

class Scene
{
public:
	//Constructor for a Scene object
	Scene(std::string scenePath);
	//Destructor for a Scene object
	~Scene();
	//Loads a Scene from a textfile
	void LoadScene(std::string scenePath);
	//Renders all objects in the scene to the window
	void RenderScene(Renderer* renderer, HWND hWnd);
	//Prepares the Scene by loading all resources for terrain, sky and entitys
	void PrepareScene(Renderer* renderer, ResourcesManager* resourceManager);
	//Removes all EntityModel objects from the entityList
	void ClearEntityList();
	//Get the camera
	EntityCamera* GetCamera();

private:
	//Terrain in the Scene
	Terrain* terrain;
	//List with EntityModel objects in the Scene
	std::list<EntityModel>* entityList;
	//Camera for the Scene
	EntityCamera* camera;
	//Skybox in the Scene
	SkyBox* sky;
	//The URL to the scenefile
	std::string scenePath;
	//Check if scene is loaded or not
	bool sceneLoaded;
	//Check if scene is prepared or not
	bool scenePrepared;
};

#endif