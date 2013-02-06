
#include "Kernel.h"

int main()
{
	Kernel* kernel = new Kernel();
	kernel->AddWindow("Window 1", 20, 50, 800, 800);
	//kernel->AddWindow("Window 2", 850, 50, 800, 800);
	kernel->LoadAndPrepareScene("scenetest.txt");
	//kernel->GetSceneManager()->AddScene("scenetest2.txt");
	kernel->LinkSceneToWindow("Window 1", "scenetest.txt");
	//kernel->LinkSceneToWindow(kernel->GetSceneManager()->GetScene("scenetest2.txt"), kernel->GetWindowManager()->GetWindow("Window 2"));
	kernel->Start();

	return 0;
};