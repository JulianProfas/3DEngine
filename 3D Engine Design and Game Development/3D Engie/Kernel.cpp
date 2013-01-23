#include "Kernel.h"

LRESULT WINAPI MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
    switch( msg )
    {
		
		case WM_DESTROY:
			PostQuitMessage(0);
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
	this->windowManager = new WindowManager();
	this->renderer = new RendererDX9();
	this->renderMap = new RenderMap();
	Kernel::inputManager = new InputManager();
	
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
	return this->windowManager;
}

/*

*/
void Kernel::Start()
{
	RenderMap::iterator it = this->renderMap->begin();
	while(it != this->renderMap->end())
	{
		Window* w = it->first;
		w->Show(SW_SHOW);
		HWND hwnd = w->getWindow();
		inputManager->AddKeyboardInput(hwnd);
		inputManager->AddMouseInput(hwnd);
		++it;
	}

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while(msg.message != WM_QUIT)
    {
		inputManager->CheckStates();

		if(PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			
			it = renderMap->begin();
			while(it != this->renderMap->end())
			{
				it->second->RenderScene(it->first->getWindow());
				++it;
			}
			
			
		}
		
    }
	

}

/*

*/
void Kernel::CleanUp()
{
	this->renderMap->clear();

	if(windowManager != NULL)
	{
		delete windowManager;
	}
	if(sceneManager != NULL)
	{
		delete sceneManager;
	}
	if(resourceManager != NULL)
	{
		delete resourceManager;
	}
	
}

void Kernel::LinkSceneToWindow(Scene* scene, Window* window)
{
	this->renderMap->insert(std::pair<Window*, Scene*>(window, scene));
}

SceneManager* Kernel::GetSceneManager()
{
	return this->sceneManager;
}

Renderer* Kernel::GetRenderer()
{
	return this->renderer;
}

void Kernel::AddWindow(std::string title, int x, int y, int width, int height)
{
	this->GetWindowManager()->AddWindow(title, x, y, width, height);

	this->renderer->InitDevice(this->GetWindowManager()->GetWindow(title)->getWindow(), width, height);

	this->resourceManager = new ResourcesManager((LPDIRECT3DDEVICE9)this->renderer->GetDevice());
	this->sceneManager = new SceneManager(this->resourceManager, this->renderer);
}
