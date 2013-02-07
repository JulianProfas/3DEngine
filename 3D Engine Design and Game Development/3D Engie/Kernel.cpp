#include "Kernel.h"

LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {	
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
    }

    return DefWindowProc(hWnd, msg, wParam, lParam);
}

WNDCLASSEX wc =
{
	sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L,
	GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
    "ENGIE", NULL
};

/*
	Constructor for a Kernel object
*/
Kernel::Kernel()
{
	RegisterClassEx(&wc);
	this->windowManager = new WindowManager();
	this->renderer = new RendererDX9();
	this->renderMap = new std::map<Window*, Scene*>();
	this->inputManager = new InputManager();
	
}

/*
	Destructor for a Kernel object
*/
Kernel::~Kernel()
{
	this->CleanUp();
}

/*
	Start rendering all scenes in the renderMap
*/
void Kernel::Start()
{
	this->isRunning = true;

	std::map<Window*, Scene*>::iterator it = this->renderMap->begin();
	while(it != this->renderMap->end())
	{
		Window* w = it->first;
		w->Show(SW_SHOW);
		HWND hwnd = w->getWindow();
		this->inputManager->AddKeyboardInput();
		this->inputManager->AddMouseInput();
		this->inputManager->GetKeyboard()->InitKeyboardInput(hwnd);
		this->inputManager->GetMouse()->InitMouseInput(hwnd);
		this->renderer->SetupViewMatrix(it->second->GetCamera()->GetPositionX(), it->second->GetCamera()->GetPositionY(), it->second->GetCamera()->GetPositionZ());
		this->renderer->SetupProjectionMatrix();
		++it;
	}

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while(msg.message != WM_QUIT & this->isRunning == true)
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
				inputManager->UpdateStates();
				EntityCamera* camera = it->second->GetCamera();

				//process keyboard input
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

				if(inputManager->GetKeyboard()->ProcessKBInput(DIK_ESCAPE))
				{
					this->isRunning = false;
				}

				//process mouse input
				camera->SetPitch(inputManager->GetMouse()->GetRelativeY());
				camera->SetYaw(inputManager->GetMouse()->GetRelativeX());

				//render the scene
				it->second->RenderScene(this->renderer, it->first->getWindow());
				++it;
			}	
		}
    }
}

/*
	Cleanup
*/
void Kernel::CleanUp()
{
	this->renderMap->clear();

	if(this->windowManager != NULL)
	{
		delete this->windowManager;
	}
	if(this->sceneManager != NULL)
	{
		delete this->sceneManager;
	}
	if(this->resourceManager != NULL)
	{
		delete this->resourceManager;
	}
	if(this->renderer != NULL)
	{
		delete this->renderer;
	}
	if(this->inputManager != NULL)
	{
		delete this->inputManager;
	}
	
}

/*
	Links a scene to a window in the renderMap
*/
void Kernel::LinkSceneToWindow(std::string window, std::string scene)
{
	this->renderMap->insert(std::pair<Window*, Scene*>(this->windowManager->GetWindow(window), this->sceneManager->GetScene(scene)));
}

/*
	Create a new window
*/
void Kernel::AddWindow(std::string title, int x, int y, int width, int height)
{
	this->windowManager->AddWindow(title, x, y, width, height);

	this->renderer->InitDevice(this->windowManager->GetWindow(title)->getWindow());

	this->resourceManager = new ResourcesManager();
	this->sceneManager = new SceneManager();
}

/*
	Creates a new scene and loads and prepares it
*/
void Kernel::LoadAndPrepareScene(std::string scenePath)
{
	this->sceneManager->AddScene(scenePath);
	Scene* scene = this->sceneManager->GetScene(scenePath);
	scene->LoadScene(scenePath);
	scene->PrepareScene(this->renderer, this->resourceManager);
}
