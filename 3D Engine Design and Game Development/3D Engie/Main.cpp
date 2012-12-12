#include "Logger.h"
#include "Window.h"
#include "WindowManager.h"

int main()
{
	WindowManager* wm = new WindowManager();
	wm->AddWindow("Window test", 250, 150, 400, 400);
	wm->GetWindow("Window test")->Show();
	
	return 0;
};