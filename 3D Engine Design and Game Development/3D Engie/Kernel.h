#ifndef ENGIE_KERNEL_H
#define ENGIE_KERNEL_H

#include "WindowManager.h"
#include "Renderer.h"
#include "RendererDX9.h"
#include "Logger.h"
#include <string>

class Kernel
{
public:
	Kernel();
	~Kernel();
	void Start();
	WindowManager* GetWindowManager();
	//LRESULT CALLBACK MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );
private:
	WindowManager* windowManager;
	Renderer* renderer;
	void CleanUp();
	
};

#endif