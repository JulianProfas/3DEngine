
#include "Logger.h"
#include "Kernel.h"
#include "RendererDX9.h"
#include "Model.h"
#include "Texture.h"
#include "ResourcesManager.h"
#include "Terrain.h"
#include "Window.h"

int main()
{
	
	Kernel* kernel = new Kernel();
	/*
	kernel->GetWindowManager()->AddWindow("Window 1", 50, 50, 200, 200);
	kernel->GetWindowManager()->AddWindow("Window 2", 250, 50, 200, 200);
	kernel->Start();
	*/
	
	Window* w = new Window("Gay", 50, 50, 768, 1024);
	
	RendererDX9* rdx9 = new RendererDX9();
	rdx9->InitDevice(w->getWindow(), 1024, 768);
	w->Show(SW_NORMAL);
	ResourcesManager* r = new ResourcesManager((LPDIRECT3DDEVICE9)rdx9->GetDevice());
	Model* m = &r->LoadModel("tiger.x");
	Model* me = &r->LoadModel("tiger.x");
	Texture* t = &r->LoadTexture("tiger.bmp");
	Texture* te = &r->LoadTexture("tiger.bmp");
	Terrain* terrain = new Terrain("heightmap.bmp", "lava.jpg", rdx9, r);

	while(true)
	{	
		rdx9->ClearScene();
		if(rdx9->BeginScene())
		{
			rdx9->SetupProjectionMatrix();
			rdx9->SetupViewMatrix();

			//set model 1 to its position using the world matrix
			rdx9->SetupWorldMatrix(10, 5, 0, 0, 0, 0, 10, 10, 10);
			// Render model 1
			for( DWORD i = 0; i < m->GetNumMaterials(); i++)
			{
				// Set the material and texture for this subset
				rdx9->SetMaterial(&m->GetMaterials()[i] );
				rdx9->SetTexture(t->getTexture()[i]);
				// Draw the mesh subset
				rdx9->DrawSubset(m->GetMesh(), i);
			}

			rdx9->SetupWorldMatrix(-10, 5, 0, 0, 0, 0, 10, 10, 10);
			// Render model 2
			for( DWORD i = 0; i < m->GetNumMaterials(); i++)
			{
				// Set the material and texture for this subset
				rdx9->SetMaterial(&me->GetMaterials()[i] );
				rdx9->SetTexture(te->getTexture()[i]);
				// Draw the mesh subset
				rdx9->DrawSubset(m->GetMesh(), i);
			}

			//Render terrain
			rdx9->SetupWorldMatrix(-128, -10, -128, 0, 0, 0, 1, 1, 1);

			rdx9->SetStreamSource(terrain->GetVertexBuffer(), sizeof(ENGIE_VERTEX));
			rdx9->SetTexture(*terrain->GetTexture()->getTexture());
			rdx9->DrawPrimitive(D3DPT_TRIANGLELIST, 0, terrain->GetNumberOfVertices()/3);

			rdx9->EndScene();

			rdx9->PresentScene();
		}
	}
	
	return 0;
};