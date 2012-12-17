#include "Logger.h"
#include "Kernel.h"

int main()
{
	Kernel* kernel = new Kernel();
	kernel->GetWindowManager()->AddWindow("Window 1", 50, 50, 200, 200);
	kernel->GetWindowManager()->AddWindow("Window 2", 250, 50, 200, 200);
	kernel->Start();


	return 0;
};