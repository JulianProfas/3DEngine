#ifndef ENGIE_KERNEL_H
#define ENGIE_KERNEL_H

#include "WindowManager.h"
#include "Renderer.h"

class Kernel
{
public:
	Kernel();
	~Kernel();
private:
	WindowManager* windowManager;
	Renderer* renderer;	
};

#endif