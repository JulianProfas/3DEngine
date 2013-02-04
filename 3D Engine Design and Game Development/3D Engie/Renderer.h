#ifndef ENGIE_RENDERER_H
#define ENGIE_RENDERER_H

#include "Model.h"
#include "Texture.h"

struct ENGIE_VERTEX
{
    FLOAT x, y, z; 
	FLOAT tu, tv; //Texture coordinates	
};

class Renderer
{
public:
	//Destructor of a Renderer object
	~Renderer() {};
	//Initializes the device of a renderer object for given HWND
	virtual HRESULT	InitDevice(HWND hWnd) = 0;
	//Sets the world matrix
	virtual void SetupWorldMatrix(float x, float y, float z, float rotX, float rotY, float rotZ, float scaleX, float scaleY, float scaleZ) = 0;
	

	//virtual	void SetupViewMatrix(float x, float y, float z, float laX, float laY, float laZ) = 0;
	
	//Sets the projection matrix
	virtual void SetupProjectionMatrix() = 0;
	//Clears a scene
	virtual void ClearScene() = 0;
	//Begins a scene
	virtual bool BeginScene() = 0;
	//Ends a scene
	virtual void EndScene() = 0;
	//Present a scene to given HWND
	virtual void PresentScene(HWND hWnd) = 0;
	//Sets a vertex buffer to a device data stream
	virtual void SetStreamSource(int buffer, int stride) = 0;
	//Renders nonindexed triangles
	virtual void DrawPrimitiveTriangle(int startVertex, int numberOfTriangles) = 0;
	//Creates a vertexbuffer
	virtual int	 CreateVertexBuffer(ENGIE_VERTEX vertices[], int numberofVertices) = 0;
	//Renders a subset of a mesh
	virtual void DrawSubset(Model* model, DWORD i) = 0;
	//Sets a texture
	virtual void SetTexture(Texture* texture) = 0;	
	//Get the device
	virtual void* GetDevice() = 0;
	//Sets the current vertex stream declaration
	virtual void SetFvF(DWORD fvf) = 0;
	//Enables or disables z-buffering
	virtual void Zenable(bool enable) = 0;

private:

};

#endif