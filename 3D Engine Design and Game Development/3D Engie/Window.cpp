#include "Window.h"
#include "Logger.h"



Window::Window(std::string title, int x, int y, int height, int width)
{
	hwnd = CreateWindow( "ENGIE", title.c_str(),
		WS_EX_LAYERED, x, y, width, height,
                              NULL, NULL, wc.hInstance, NULL );
	Logger::GetInstance()->Write("Window aangemaakt");
}

HWND Window::getWindow()
{
	return hwnd;
}

void Window::Show(int showWindow)
{
	ShowWindow(hwnd, showWindow);
	UpdateWindow(hwnd);

	Logger::GetInstance()->Write("Showing window ");

}