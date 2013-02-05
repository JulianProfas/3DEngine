#include "Window.h"

/*
	Constructor for a Window object
	@param title, title for the Window
	@param x, the x position of the Window
	@param y, the y position of the Window
	@param width, the width of the Window
	@param height, the height of the Window
*/
Window::Window(std::string title, int x, int y, int height, int width)
{
	this->title = title;

	this->hwnd = CreateWindow( "ENGIE", title.c_str(),
		WS_EX_LAYERED, x, y, width, height,
		NULL, NULL, wc.hInstance, NULL );

	Logger::GetInstance()->Write("Window " + title + " created");
}

/*
	Shows the Window
	@param showWindow, controls how the Window is to be shown
*/
void Window::Show(DWORD showWindow)
{
	ShowWindow(hwnd, showWindow);
	UpdateWindow(hwnd);

	Logger::GetInstance()->Write("Showing window: " + this->title);
}

/*
	Get the HWND from the Window
*/
HWND Window::getWindow()
{
	return hwnd;
}

