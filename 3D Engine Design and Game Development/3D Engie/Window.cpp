#include "Window.h"
#include "Logger.h"

LRESULT WINAPI MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
    switch( msg )
    {
        case WM_DESTROY:
            
            PostQuitMessage( 0 );
            return 0;

        case WM_PAINT:
            
            ValidateRect( hWnd, NULL );
            return 0;
    }

    return DefWindowProc( hWnd, msg, wParam, lParam );
}

WNDCLASSEX wc =
{
    sizeof( WNDCLASSEX ), CS_CLASSDC, MsgProc, 0L, 0L,
	GetModuleHandle( NULL ), NULL, NULL, NULL, NULL,
    "ENGIE", NULL
};

Window::Window(std::string title, int x, int y, int height, int width)
{
	RegisterClassEx( &wc );
	hwnd = CreateWindow( "ENGIE", title.c_str(),
		WS_EX_LAYERED, x, y, width, height,
                              NULL, NULL, wc.hInstance, NULL );
	Logger::GetInstance()->Write("Window aangemaakt");
}


void Window::Show(int showWindow)
{
	ShowWindow(hwnd, showWindow);
	UpdateWindow(hwnd);

	Logger::GetInstance()->Write("Showing window ");

	MSG msg;
    while(GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}