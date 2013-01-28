
#include "Logger.h"
#include "Kernel.h"
#include "RendererDX9.h"
#include "Model.h"
#include "Texture.h"
#include "ResourcesManager.h"
#include "Terrain.h"
#include "Window.h"
#include "camera.h"
#include "Scene.h"
#include "EntityModel.h"

int main()
{

	Kernel* kernel = new Kernel();
	kernel->AddWindow("Window 1", 20, 50, 800, 800);
	kernel->AddWindow("Window 2", 850, 50, 800, 800);
	kernel->GetSceneManager()->AddScene("scenetest.txt");
	kernel->GetSceneManager()->AddScene("scenetest2.txt");
	kernel->LinkSceneToWindow(kernel->GetSceneManager()->GetScene("scenetest.txt"), kernel->GetWindowManager()->GetWindow("Window 1"));
	kernel->LinkSceneToWindow(kernel->GetSceneManager()->GetScene("scenetest2.txt"), kernel->GetWindowManager()->GetWindow("Window 2"));
	kernel->Start();


	/*
	Window* w = new Window("Gay", 50, 50, 500, 500);
	//Window* w2 = new Window("Lord", 250, 50, 200, 200);
	
	Renderer* rdx9 = new RendererDX9();
	rdx9->InitDevice(w->getWindow(), 500, 500);
	w->Show(SW_NORMAL);
	//rdx9->InitDevice(w2->getWindow(), 200, 200);
	//w2->Show(SW_NORMAL);
	ResourcesManager* r = new ResourcesManager((LPDIRECT3DDEVICE9)rdx9->GetDevice());
	//EntityModel* e = new EntityModel(-20, 5, 0, 4.725, 0, 0, 15, 15, 15, "tiger.x", "tiger.bmp", r);
	//EntityModel* en = new EntityModel(20, 5, 0, 1.725, 0, 0, 10, 10, 10, "tiger.x", "tiger.bmp", r);
	
	Model* m = &r->LoadModel("tiger.x");
	Model* me = &r->LoadModel("tiger.x");
	Texture* t = &r->LoadTexture("tiger.bmp");
	Texture* te = &r->LoadTexture("tiger.bmp");
	
	//Terrain* terrain = new Terrain("heightmap.bmp", "lava.jpg", rdx9, r);
	Camera TheCamera(Camera::LANDOBJECT);

	Scene* scene = new Scene(rdx9, r, "scenetest.txt");

	while(true)
	{
		//hier
		if( ::GetAsyncKeyState('W') & 0x8000f )
			TheCamera.walk(4.0f * timeDelta);

		if( ::GetAsyncKeyState('S') & 0x8000f )
			TheCamera.walk(-4.0f * timeDelta);

		if( ::GetAsyncKeyState('A') & 0x8000f )
			TheCamera.strafe(-4.0f * timeDelta);

		if( ::GetAsyncKeyState('D') & 0x8000f )
			TheCamera.strafe(4.0f * timeDelta);

		if( ::GetAsyncKeyState('R') & 0x8000f )
			TheCamera.fly(4.0f * timeDelta);

		if( ::GetAsyncKeyState('F') & 0x8000f )
			TheCamera.fly(-4.0f * timeDelta);

		if( ::GetAsyncKeyState(VK_UP) & 0x8000f )
			TheCamera.pitch(1.0f * timeDelta);

		if( ::GetAsyncKeyState(VK_DOWN) & 0x8000f )
			TheCamera.pitch(-1.0f * timeDelta);

		if( ::GetAsyncKeyState(VK_LEFT) & 0x8000f )
			TheCamera.yaw(-1.0f * timeDelta);
			
		if( ::GetAsyncKeyState(VK_RIGHT) & 0x8000f )
			TheCamera.yaw(1.0f * timeDelta);

		if( ::GetAsyncKeyState('N') & 0x8000f )
			TheCamera.roll(1.0f * timeDelta);

		if( ::GetAsyncKeyState('M') & 0x8000f )
			TheCamera.roll(-1.0f * timeDelta);

		// Update the view matrix representing the cameras 
        // new position/orientation.
		D3DXMATRIX V;
		TheCamera.getViewMatrix(&V);
		//rdx9->SetTransform(D3DTS_VIEW, &V);
		//hier
		
		rdx9->ClearScene();
		if(rdx9->BeginScene())
		{
			rdx9->SetupProjectionMatrix();
			rdx9->SetupViewMatrix();

			e->renderEntityModel(rdx9);
			en->renderEntityModel(rdx9);

			
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
			
			terrain->RenderTerrain(rdx9);
			rdx9->EndScene();

			rdx9->PresentScene(w->getWindow());
			rdx9->PresentScene(w2->getWindow());
		}
		

		scene->RenderScene(w->getWindow());
	}
	*/
	return 0;
};