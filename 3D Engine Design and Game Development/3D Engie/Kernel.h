#ifndef ENGIE_KERNEL_H
#define ENGIE_KERNEL_H

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