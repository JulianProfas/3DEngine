#ifndef ENGIE_KERNEL_H
#define ENGIE_KERNEL_H

#include "WindowManager.h"
#include "Window.h"
#include "InputManager.h"
#include "ResourcesManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "RendererDX9.h"
#include "Logger.h"
#include <string>
#include <map>

class Kernel
{
public:
	//Constructor for a Kernel object
	Kernel();
	//Destructor for a Kernel object
	~Kernel();
	//Start rendering all scenes in the renderMap
	void Start();
	//Create a new window
	void AddWindow(std::string title, int x, int y, int width, int height);
	//Links a scene to a window in the renderMap
	void LinkSceneToWindow(std::string window, std::string scene);
	//Creates a new scene and loads and prepares it
	void LoadAndPrepareScene(std::string scenePath);

private:
	//Manager to manage all windows
	WindowManager* windowManager;
	//Manager to manage all input
	InputManager* inputManager;
	//Renderer
	Renderer* renderer;
	//Manager to manage all resources
	ResourcesManager* resourceManager;
	//Manager to manage all scenes
	SceneManager* sceneManager;
	//Map to know which scene must be drawn in which window
	std::map<Window*, Scene*>* renderMap;
	//Cleanup
	void CleanUp();
	//check to see if kernel is running
	bool isRunning;
};

#endif