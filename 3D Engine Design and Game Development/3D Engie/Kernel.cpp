#include "Kernel.h"

LRESULT WINAPI MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
    switch( msg )
    {
		
		case WM_DESTROY:
			PostQuitMessage(0);
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

/*

*/
Kernel::Kernel()
{
	RegisterClassEx( &wc );
	Kernel::windowManager = new WindowManager();
	//Kernel::renderer = new RendererDX9();
}

/*

*/
Kernel::~Kernel()
{
	this->CleanUp();
}

/*

*/
WindowManager* Kernel::GetWindowManager()
{
	return windowManager;
}

/*

*/
void Kernel::Start()
{
	WindowMap::iterator it = this->windowManager->GetWindowMap()->begin();
	while(it != this->windowManager->GetWindowMap()->end())
	{
		it->second->Show(SW_SHOW);
		it++;
	}

	MSG msg;
	ZeroMemory( &msg, sizeof( msg ) );
	while(msg.message != WM_QUIT)
    {
		//std::cout << this->GetWindowManager()->GetWindowMap()->size() << std::endl;
		
		if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}
		
    }

}

/*

*/
void Kernel::CleanUp()
{
	if(windowManager != NULL)
	{
		delete windowManager;
	}
}






