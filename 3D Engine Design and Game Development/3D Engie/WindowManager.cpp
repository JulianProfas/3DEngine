#include "WindowManager.h"
#include "Logger.h"

/*
	Constructor.
*/
WindowManager::WindowManager()
{
	windows = new WindowMap();
	Logger::GetInstance()->Write("WindowManager aangemaakt");
}

/*
	Destructor.
*/
WindowManager::~WindowManager()
{
	ClearWindowMap();
	Logger::GetInstance()->Write("WindowManager verwijderd");
}

/*
	Add a window to the windowMap.
*/
void WindowManager::AddWindow(std::string title, int x, int y, int width, int height)
{
	Window* w = new Window(title, x, y, width, height);
	Logger::GetInstance()->Write("Window " + title + " aangemaakt");
	windows->insert(std::pair<std::string, Window*>(title, w));
	Logger::GetInstance()->Write("Window " + title + " toegevoegd aan WindowsMap");
}

/*
	Remove an element from the container: the destructor is called from the removed element. 
*/
void WindowManager::RemoveWindow(std::string title)
{
	windows->erase(title);
}

/*	
	All the elements in the container are dropped: their destructors are called, 
	and then they are removed from the container, leaving it with a size of 0.
*/
void WindowManager::ClearWindowMap()
{
	windows->clear();
}

/*
	Get the window by title.
*/
Window* WindowManager::GetWindow(std::string title)
{
	return windows->find(title)->second;
}

/*

*/
WindowMap* WindowManager::GetWindowMap()
{
	return windows;
}

/*

*/
void WindowManager::RemoveWindow(HWND hwnd)
{
	WindowMap::iterator it = windows->begin();
	bool found = false;
	while(found == false)
	{
		Window* temp = it->second;
		if(hwnd == temp->getWindow())
		{
			windows->erase(it);
		}
	} 
}