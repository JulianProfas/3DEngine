#include "Kernel.h"

LRESULT WINAPI MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
    switch( msg )
    {
        case WM_CLOSE:
			DestroyWindow(hWnd);
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
    while(GetMessage(&msg, NULL, 0, 0))
    {
		std::cout << this->GetWindowManager()->GetWindowMap()->size() << std::endl;
		
        TranslateMessage(&msg);
        DispatchMessage(&msg);
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






