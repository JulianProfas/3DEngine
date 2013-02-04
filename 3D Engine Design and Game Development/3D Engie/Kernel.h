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
	Kernel();
	~Kernel();
	void Start();
	WindowManager* GetWindowManager();
	SceneManager* GetSceneManager();
	Renderer* GetRenderer();
	void AddWindow(std::string title, int x, int y, int width, int height);
	void LinkSceneToWindow(Scene* scene, Window* window);
	//LRESULT CALLBACK MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );
private:
	WindowManager* windowManager;
	InputManager* inputManager;
	Renderer* renderer;
	ResourcesManager* resourceManager;
	SceneManager* sceneManager;
	std::map<Window*, Scene*>* renderMap;
	void CleanUp();
};

#endif