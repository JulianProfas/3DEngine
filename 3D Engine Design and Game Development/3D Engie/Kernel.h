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
private:
	WindowManager* windowManager;
	Renderer* renderer;
	void CleanUp();
	//LRESULT WINAPI MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );
};

#endif