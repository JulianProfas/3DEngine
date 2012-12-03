#ifndef ENGIE_WINDOWMANAGER_H
#define ENGIE_WINDOWMANAGER_H

class WindowManager
{
public:
	WindowMager();
    ~WindowManager();
	CreateWindow();
	RemoveWindow();
private:
	List* windows;
}

#endif