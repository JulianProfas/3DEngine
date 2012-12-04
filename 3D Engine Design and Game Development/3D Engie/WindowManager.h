#ifndef ENGIE_WINDOWMANAGER_H
#define ENGIE_WINDOWMANAGER_H

class WindowManager
{
public:
	WindowManager();
    ~WindowManager();
	void CreateWindow();
	void RemoveWindow();
private:
	List* windows;
};

#endif