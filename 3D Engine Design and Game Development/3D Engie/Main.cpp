
#include "Kernel.h"

int main()
{
	Kernel* kernel = new Kernel();
	kernel->AddWindow("Window 1", 20, 50, 800, 800);
	kernel->LoadAndPrepareScene("scenetest.txt");
	kernel->LinkSceneToWindow("Window 1", "scenetest.txt");
	kernel->Start();

	delete kernel;
	return 0;
};