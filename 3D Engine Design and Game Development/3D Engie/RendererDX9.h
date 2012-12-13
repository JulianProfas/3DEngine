#ifndef RENDERERDX9_H
#define RENDERERDX9_H
#include <Windows.h>
#include <mmsystem.h>
#include <d3dx9.h>
#include <strsafe.h>
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
	void Render();
private:

};

#endif