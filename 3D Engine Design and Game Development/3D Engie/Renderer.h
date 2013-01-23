#ifndef ENGIE_RENDERER_H
#define ENGIE_RENDERER_H

#include <d3d9.h>
#include <d3dx9.h>

struct ENGIE_VERTEX
{
    FLOAT x, y, z; 
	FLOAT tu, tv; //Texture coordinates	
};

class Renderer
{
public:
	~Renderer() {};
	virtual HRESULT	InitDevice(HWND hWnd, int width, int height) = 0;
	virtual void	SetupWorldMatrix(float x, float y, float z, float rotX, float rotY, float rotZ, float scaleX, float scaleY, float scaleZ) = 0;
	virtual	void	SetupViewMatrix(float x, float y, float z, float laX, float laY, float laZ) = 0;
	virtual void	SetupProjectionMatrix() = 0;
	virtual void	CleanUp() = 0;
	virtual void	ClearScene() = 0;
	virtual bool	BeginScene() = 0;
	virtual void	EndScene() = 0;
	virtual void	PresentScene(HWND hWnd) = 0;
	virtual void	SetStreamSource(LPDIRECT3DVERTEXBUFFER9 buffer, unsigned int Stride) = 0;
	virtual void	DrawPrimitive(D3DPRIMITIVETYPE PrimitiveType, unsigned int StartVertex, unsigned int NumberOfPrimitives) = 0;
	virtual LPDIRECT3DVERTEXBUFFER9		CreateVertexBuffer(ENGIE_VERTEX Vertices[], int NumberofVertices) = 0;
	virtual void	DrawSubset(LPD3DXMESH leakMesh, DWORD i) = 0;
	virtual void	SetTexture(LPDIRECT3DTEXTURE9 Texture) = 0;	
	virtual void*	GetDevice() = 0;	
private:
};

#endif