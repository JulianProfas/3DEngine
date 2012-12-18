#ifndef ENGIE_RENDERER_H
#define ENGIE_RENDERER_H

class Renderer
{
public:
	~Renderer();
	virtual bool InitDevice(HWND hwnd) = 0;
	virtual void BeginScene() = 0;
	virtual void ClearScene() = 0;
	virtual void EndScene() = 0;
	virtual void PresentScene() = 0;
	virtual void DrawPrimitive() = 0;
private:
};

#endif