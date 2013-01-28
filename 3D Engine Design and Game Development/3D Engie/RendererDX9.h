#ifndef RENDERERDX9_H
#define RENDERERDX9_H

#include <Windows.h>
#include <d3dx9.h>
#include "Model.h"
#include "Texture.h"
#include "Renderer.h"
#include <map>



typedef std::map<int, LPDIRECT3DVERTEXBUFFER9> VertexBufferMap;

class RendererDX9 : public Renderer
{
public:
	RendererDX9();
	~RendererDX9();	
	HRESULT	InitDevice(HWND hWnd, int width, int height);
	void SetupWorldMatrix(float x, float y, float z, float rotX, float rotY, float rotZ, float scaleX, float scaleY, float scaleZ);
	//void SetupViewMatrix(float x, float y, float z, float laX, float laY, float laZ);
	void SetupViewMatrix(D3DXMATRIX viewMatrix);
	void SetupProjectionMatrix();
	void ClearScene();
	bool BeginScene();
	void EndScene();
	void PresentScene(HWND hWnd);
	int	 CreateVertexBuffer(ENGIE_VERTEX Vertices[], int NumberofVertices);
	void SetStreamSource(int buffer, unsigned int Stride);
	void SetFvF(DWORD fvf);
	void DrawPrimitive(D3DPRIMITIVETYPE PrimitiveType, unsigned int StartVertex, unsigned int NumberOfPrimitives);
	void DrawSubset(LPD3DXMESH mesh, DWORD i);
	void SetMaterial(D3DMATERIAL9 *MeshMaterial);
	void SetTexture(LPDIRECT3DTEXTURE9 Texture);
	void Zenable(bool enable);
	void* GetDevice();
private:
	void CleanUp();
	VertexBufferMap VBM;
	LPDIRECT3D9         g_pD3D; // Used to create the D3DDevice
	LPDIRECT3DDEVICE9   g_pd3dDevice; // Our rendering device
	int mapIndex;
};

#endif