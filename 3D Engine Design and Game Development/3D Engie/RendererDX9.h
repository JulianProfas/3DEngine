#ifndef RENDERERDX9_H
#define RENDERERDX9_H

#include "renderer.h"

class rendererDX9 : public renderer
{
public:
	rendererDX9();
	~rendererDX9();
	bool InitD3D(HWND hwnd);
	void BeginScene();
	void ClearScene();
	void EndScene();
	void PresentScene();
	void DrawPrimitive();
private:

};

#endif