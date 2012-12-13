#include "Logger.h"
#include "Window.h"
#include "WindowManager.h"
#include "RendererDX9.h"

int main()
{
	WindowManager* wm = new WindowManager();
	wm->AddWindow("Window test", 250, 150, 400, 400);
	wm->GetWindow("Window test")->Show(SW_NORMAL);
	

	return 0;
};