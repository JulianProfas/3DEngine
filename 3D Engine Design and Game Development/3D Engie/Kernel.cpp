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
	this->renderMap = new std::map<Window*, Scene*>();
	this->inputManager = new InputManager();
	
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
	std::map<Window*, Scene*>::iterator it = this->renderMap->begin();
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
				inputManager->CheckStates(it->second);
				EntityCamera* camera = it->second->GetCamera();
				if(inputManager->GetKeyboard()->ProcessKBInput(DIK_W))
				{
					camera->MoveForward();
				}

				if(inputManager->GetKeyboard()->ProcessKBInput(DIK_S))
				{
					camera->MoveBackward();
				}

				if(inputManager->GetKeyboard()->ProcessKBInput(DIK_A))
				{
					camera->MoveLeft();
				}

				if(inputManager->GetKeyboard()->ProcessKBInput(DIK_D))
				{
					camera->MoveRight();
				}

				if(inputManager->GetKeyboard()->ProcessKBInput(DIK_SPACE))
				{
					camera->MoveUp();
				}

				if(inputManager->GetKeyboard()->ProcessKBInput(DIK_C))
				{
					camera->MoveDown();
				}

				if(inputManager->GetKeyboard()->ProcessKBInput(DIK_LEFT))
				{
						camera->SetYaw(0.1);
				}
				if(inputManager->GetKeyboard()->ProcessKBInput(DIK_RIGHT))
				{
						camera->SetYaw(-0.1);
				}
				if(inputManager->GetKeyboard()->ProcessKBInput(DIK_UP))
				{
						camera->SetPitch(0.1);
				}
				if(inputManager->GetKeyboard()->ProcessKBInput(DIK_DOWN))
				{
						camera->SetPitch(-0.1);
				}
				std::cout << inputManager->GetMouse()->GetRelativeX() << std::endl;
				camera->SetPitch(inputManager->GetMouse()->GetRelativeY());
				camera->SetYaw(inputManager->GetMouse()->GetRelativeX());
				it->second->RenderScene(this->renderer, it->first->getWindow());
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

	this->renderer->InitDevice(this->GetWindowManager()->GetWindow(title)->getWindow());

	this->resourceManager = new ResourcesManager();
	this->sceneManager = new SceneManager();
}

void Kernel::LoadAndPrepareScene(std::string scenePath)
{
	this->GetSceneManager()->AddScene(scenePath);
	Scene* scene = this->GetSceneManager()->GetScene(scenePath);
	scene->LoadScene(this->renderer, scenePath);
	scene->PrepareScene(this->renderer, this->resourceManager);
}