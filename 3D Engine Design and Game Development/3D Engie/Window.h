#ifndef ENGIE_WINDOW_H
#define ENGIE_WINDOW_H

#include <windows.h>
#include <string>
#include "Logger.h"

extern WNDCLASSEX wc;

class Window
{
public:
	//Constructor for a Window object
	Window(std::string title, int x, int y, int height, int width);
	//Destructor for a Window object
	~Window();
	//Shows the Window
	void Show(DWORD showWindow);
	//Get the HWND from the window
	HWND* getWindow();

private:
	//The HWND of the Window
	HWND* hwnd;
	//The title of the Window
	std::string title;
};

#endif
