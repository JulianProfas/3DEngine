#ifndef ENGIE_WINDOW_H
#define ENGIE_WINDOW_H

#include <windows.h>
#include <string>

class Window
{
public:
	Window(int x, int y, int heigth, int width, std::string title);
	~Window();
	void Show();
private:
	HWND hwnd;
	LRESULT WINAPI MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );
};

#endif
