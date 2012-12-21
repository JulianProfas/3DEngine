#ifndef RENDERERDX9_H
#define RENDERERDX9_H
#include <Windows.h>
#include <mmsystem.h>
#include <d3dx9.h>
#include <strsafe.h>
#include "Model.h"
//#include "renderer.h"

class RendererDX9// : public Renderer
{
public:
	RendererDX9();
	HRESULT InitD3D(HWND hwnd);
	/*void BeginScene();
	void ClearScene();
	void EndScene();
	void PresentScene();
	void DrawPrimitive();*/
	LPDIRECT3DDEVICE9 GetDevice();
	void Render(Model* m);
private:
	void CleanUp();
	LPDIRECT3D9         g_pD3D; // Used to create the D3DDevice
	LPDIRECT3DDEVICE9   g_pd3dDevice; // Our rendering device
};

#endif