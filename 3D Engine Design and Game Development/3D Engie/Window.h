#ifndef ENGIE_WINDOW_H
#define ENGIE_WINDOW_H

#include <windows.h>
#include <string>

extern WNDCLASSEX wc;

class Window
{
public:
	Window(std::string title, int x, int y, int heigth, int width );
	~Window();
	void Show(int showWindow);
	HWND getWindow();
private:
	HWND hwnd;
	LRESULT WINAPI MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );
};

#endif
