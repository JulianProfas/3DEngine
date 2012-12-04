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
    "D3D Tutorial", NULL
};

Window::Window(int x, int y, int height, int width, std::string title)
{
	RegisterClassEx( &wc );
	hwnd = CreateWindow( "D3D Tutorial", title.c_str(),
                              WS_OVERLAPPEDWINDOW, x, y, width, height,
                              NULL, NULL, wc.hInstance, NULL );
	Logger::GetInstance()->Write("Window aangemaakt");
}


void Window::Show()
{
	ShowWindow(hwnd, SW_SHOWDEFAULT);
	UpdateWindow(hwnd);

	Logger::GetInstance()->Write("Showing window");

	MSG msg;
    while( GetMessage( &msg, NULL, 0, 0 ) )
    {
        TranslateMessage( &msg );
        DispatchMessage( &msg );
    }
}