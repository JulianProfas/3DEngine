
#include "Logger.h"
#include "Kernel.h"
#include "RendererDX9.h"
#include "Model.h"
#include "Window.h"

int main()
{
	
	Kernel* kernel = new Kernel();
	/*
	kernel->GetWindowManager()->AddWindow("Window 1", 50, 50, 200, 200);
	kernel->GetWindowManager()->AddWindow("Window 2", 250, 50, 200, 200);
	kernel->Start();
	*/
	
	Window* w = new Window("Gay", 50, 50, 200, 200);
	
	RendererDX9* rdx9 = new RendererDX9();
	rdx9->InitD3D(w->getWindow());
	w->Show(SW_NORMAL);
	Model* m = new Model(rdx9->GetDevice(), "awdk");
	

	while(true)
	{
		rdx9->Render(m);
	}
	
	return 0;
};