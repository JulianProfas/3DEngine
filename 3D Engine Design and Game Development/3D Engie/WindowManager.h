#ifndef ENGIE_WINDOWMANAGER_H
#define ENGIE_WINDOWMANAGER_H

#include <string>
#include "Window.h"
#include "Logger.h"
#include <map>

class WindowManager
{
public:
	//Constructor for a WindowManager object
	WindowManager();
	//Destructor for a WindowManager object
    ~WindowManager();
	//Creates and add a window to the windowMap
	void AddWindow(std::string title, int x, int y, int width, int height);
	//Remove a window from the windowMap
	void RemoveWindow(std::string title);
	//Removes all windows from the windowMap
	void ClearWindowMap();
	//Get a Window object
	Window* GetWindow(std::string title);

private:
	//Map to hold Window objects
	std::map<std::string, Window*> windowMap;
};

#endif