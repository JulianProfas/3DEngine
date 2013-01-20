#ifndef RENDERERDX9_H
#define RENDERERDX9_H

#include <Windows.h>
#include <d3dx9.h>
#include "Model.h"
#include "Texture.h"
#include "Renderer.h"

#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_TEX1)

class RendererDX9 : public Renderer
{
public:
	RendererDX9();
	~RendererDX9();	
	HRESULT	InitDevice(HWND hWnd, int width, int height);
	void SetupWorldMatrix(float x, float y, float z, float rotX, float rotY, float rotZ, float scaleX, float scaleY, float scaleZ);
	void SetupViewMatrix();
	void SetupProjectionMatrix();
	void ClearScene();
	bool BeginScene();
	void EndScene();
	void PresentScene(HWND hWnd);
	LPDIRECT3DVERTEXBUFFER9		CreateVertexBuffer(ENGIE_VERTEX Vertices[], int NumberofVertices);
	void SetStreamSource(LPDIRECT3DVERTEXBUFFER9 buffer, unsigned int Stride);
	void SetFvF(DWORD fvf);
	void DrawPrimitive(D3DPRIMITIVETYPE PrimitiveType, unsigned int StartVertex, unsigned int NumberOfPrimitives);
	void DrawSubset(LPD3DXMESH leakMesh, DWORD i);
	void SetMaterial(D3DMATERIAL9 *MeshMaterial);
	void SetTexture(LPDIRECT3DTEXTURE9 Texture);
	void Zenable(bool enable);
	void* GetDevice();
private:
	void CleanUp();
	LPDIRECT3D9         g_pD3D; // Used to create the D3DDevice
	LPDIRECT3DDEVICE9   g_pd3dDevice; // Our rendering device
};

#endif