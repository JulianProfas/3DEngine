#ifndef RENDERERDX9_H
#define RENDERERDX9_H

#include <Windows.h>
#include <d3dx9.h>
#include <d3dx9math.h>
#include <d3dx9math.inl>
#include <vector>
#include "Model.h"
#include "EntityCamera.h"
#include "Texture.h"
#include "Renderer.h"
#include <map>
#include "Logger.h"

#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_TEX1)

class RendererDX9 : public Renderer
{
public:
	//Constructor for a RendererDX9 object
	RendererDX9();
	//Destructor for a RendererDX9 object
	~RendererDX9();	
	//Initializes the device of a renderer object for given HWND
	HRESULT	InitDevice(HWND hWnd);
	//Sets the world matrix
	//void SetupWorldMatrix(float x, float y, float z, float rotX, float rotY, float rotZ, float scaleX, float scaleY, float scaleZ);
	
	
	//void SetupViewMatrix(float x, float y, float z, float laX, float laY, float laZ);
	//void SetupViewMatrix(D3DXMATRIX viewMatrix);
	
	//Sets the projection matrix
	void SetupProjectionMatrix();
	//Clears a scene
	void ClearScene();
	//Begins a scene
	bool BeginScene();
	//Ends a scene
	void EndScene();
	//Present a scene to given HWND
	void PresentScene(HWND hWnd);
	//Sets a vertex buffer to a device data stream
	void SetStreamSource(int buffer, int stride);
	//Renders nonindexed triangles
	void DrawPrimitiveTriangle(int startVertex, int numberOfTriangles);
	//Creates a vertexbuffer and adds it to the vertexBufferMap
	int	 CreateVertexBuffer(ENGIE_VERTEX vertices[], int numberofVertices);
	//Renders a subset of a mesh
	void DrawSubset(Model* model, DWORD i);
	//Sets a texture
	void SetTexture(Texture* texture);
	//Sets a material
	void SetMaterial(Model* model, int materialIndex);
	//Sets the current vertex stream declaration
	void SetFvF(DWORD fvf);
	//Enables or disables z-buffering
	void Zenable(bool enable);
	//Get the device
	void* GetDevice();
	void moveMatrix(float Ox, float Oy, float Oz, float Px, float Py, float Pz);
	void SetupWorldMatrix(float x, float y, float z, float rotX, float rotY, float rotZ, float scaleX, float scaleY, float scaleZ, EntityCamera* camera);

private:
	//Releases the device and the D3D object
	void CleanUp();

	//Map for holding different Vertex Buffers
	std::map<int, LPDIRECT3DVERTEXBUFFER9> vertexBufferMap;
	//d3d object
	LPDIRECT3D9 d3d; 
	//Directx 9 rendering device
	LPDIRECT3DDEVICE9 device;
	//Index for the vertexBufferMap
	int mapIndex;
};

#endif