#ifndef ENGIE_WINDOWMANAGER_H
#define ENGIE_WINDOWMANAGER_H

#include <string>
#include "Window.h"
#include <map>

typedef std::map<std::string, Window*> WindowMap;

class WindowManager
{
public:
	WindowManager();
    ~WindowManager();
	void AddWindow(std::string title, int x, int y, int width, int height);
	void RemoveWindow(std::string title);
	void ClearWindowMap();
	Window* GetWindow(std::string title);
private:
	WindowMap* windows;
};

#endif