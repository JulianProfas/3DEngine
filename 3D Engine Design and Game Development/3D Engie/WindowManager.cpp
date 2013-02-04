#include "WindowManager.h"

/*
	Constructor for a WindowManager object
*/
WindowManager::WindowManager()
{
	Logger::GetInstance()->Write("WindowManager created");
}

/*
	Destructor for a WindowManager object
*/
WindowManager::~WindowManager()
{
	this->ClearWindowMap();
	Logger::GetInstance()->Write("WindowManager deleted");
}

/*
	Create and add a Window to the windowMap
	@param title, title for the Window
	@param x, the x position of the Window
	@param y, the y position of the Window
	@param width, the width of the Window
	@param height, the height of the Window
*/
void WindowManager::AddWindow(std::string title, int x, int y, int width, int height)
{
	//Creates a new Window object
	Window* w = new Window(title, x, y, width, height);
	
	//Insert the newly created Window in the windowMap
	this->windowMap.insert(std::pair<std::string, Window*>(title, w));
	Logger::GetInstance()->Write("Window " + title + " inserted to windowMap");
}

/*
	Remove a Window from the WindowMap
	@param title, title of the Window that needs to be removed
*/
void WindowManager::RemoveWindow(std::string title)
{
	this->windowMap.erase(title);
}

/*	
	Removes all windows from the windowMap
*/
void WindowManager::ClearWindowMap()
{
	this->windowMap.clear();
}

/*
	Get a Window object
	@param title, title of the Window you want to get returned
*/
Window* WindowManager::GetWindow(std::string title)
{
	return this->windowMap.find(title)->second;
}
