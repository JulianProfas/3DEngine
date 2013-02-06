#include "RendererDX9.h"

/*
	Constructor for a RendererDX9 object
*/
RendererDX9::RendererDX9()
{
	this->d3d = NULL; 
	this->device = NULL;
	this->mapIndex = 0;

	Logger::GetInstance()->Write("RendererDX9 created");
}

/*
	Destructor for a RendererDX9 object
*/
RendererDX9::~RendererDX9()
{
	this->CleanUp();

	Logger::GetInstance()->Write("RendererDX9 destroyed");
}

/*
	Initializes the device of a renderer object for given HWND
	@param hWnd, the HWND needed to create the device
*/
HRESULT RendererDX9::InitDevice(HWND hWnd)
{
	// Create the D3D object.
    if(NULL == (this->d3d = Direct3DCreate9(D3D_SDK_VERSION)))
	{
		Logger::GetInstance()->Write("Failed to create the D3D object");
        return E_FAIL;
	}

	D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory( &d3dpp, sizeof( d3dpp ) );
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	if(FAILED(this->d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
                                      D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                                      &d3dpp, &device)))
    {
		Logger::GetInstance()->Write("Failed to create the device");
        return E_FAIL;
    }

    // Turn on ambient lighting 
	this->device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);	//Counter Clockwise Cullmode
	this->device->SetRenderState(D3DRS_LIGHTING, FALSE ); //No lightning
    this->device->SetRenderState( D3DRS_ZENABLE, TRUE ); //Z buffer on
	this->device->SetRenderState(D3DRS_AMBIENT, 0xffffffff ); //Ambient is white
	this->device->SetRenderState(D3DRS_ALPHABLENDENABLE, true ); //Turn Alphablending on
	this->device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA ); //Type alphablending
	this->device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA); //Type alphablending

    return S_OK;
}

/*
	Releases the device and D3D object
*/
void RendererDX9::CleanUp()
{
	if(NULL != this->device)
	{
        this->device->Release();
	}

	if(NULL != this->d3d)
	{
        this->d3d->Release();
	}
}

/*
	Clears the scene
*/
void RendererDX9::ClearScene()
{
	 // Clear the backbuffer to a blue color
    this->device->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);
	// Clear the z buffer
	this->device->Clear(0, NULL, D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);
}

/*
	Begins the scene
*/
bool RendererDX9::BeginScene()
{
	if(NULL == this->device)
	{
       return false;
	}

    if(SUCCEEDED(this->device->BeginScene()))
    {
		return true;
	}
	return false;
}

/*
	Ends the scene
*/
void RendererDX9::EndScene()
{	
     this->device->EndScene();
}

/*
	Present a scene to given HWND
	@param hWnd, The HWND that needs to display the scene
*/
void RendererDX9::PresentScene(HWND hWnd)
{
    this->device->Present(NULL, NULL, hWnd, NULL);
}

/*
	Get the device
*/
void* RendererDX9::GetDevice()
{
	return this->device;
}

/*
	Sets the world matrix
	@param x, the x position
	@param y, the y position
	@param z, the z position
	@param rotX, the x rotation
	@param rotY, the y rotation
	@param rotZ, the Z rotation
	@param scaX, the x scaling
	@param scaY, the y scaling
	@param scaZ, the z scaling
	@param camera, EntityCamera object for transforming the world matrix
*/
void RendererDX9::SetupWorldMatrix(float x, float y, float z, float rotX, float rotY, float rotZ, float scaleX, float scaleY, float scaleZ, EntityCamera* camera)
{
	//The Matrix variables
	D3DXMATRIXA16 matWorld;
	D3DXMATRIXA16 matCam;
	D3DXMATRIXA16 matWorldRot;
	D3DXMATRIXA16 matWorldTrans;
	D3DXMATRIXA16 model;
	D3DXMATRIXA16 modelTrans;
	D3DXMATRIXA16 modelRot;
	D3DXMATRIXA16 modelRotZ;
	D3DXMATRIXA16 modelRotY;
	D3DXMATRIXA16 modelRotX;
	D3DXMATRIXA16 modelScale;

	//Get the Camera variables
	float newX = camera->GetPositionX() ;
	float newY = camera->GetPositionY() ;
	float newZ = camera->GetPositionZ() ;
	float newRX =  camera->GetPitch() ;
	float newRY =  camera->GetYaw() ;
	
	//Setting the matrix of a model/object
	D3DXMatrixScaling( &modelScale, scaleX, scaleY, scaleZ);
	D3DXMatrixTranslation( &modelTrans, x, y, z);
	D3DXMatrixMultiply(&model, &modelScale, &modelTrans);
	D3DXMatrixRotationY(&modelRotY, rotY);
	D3DXMatrixRotationX(&modelRotX, rotX);
	D3DXMatrixMultiply(&modelRot, &modelRotY, &modelRotX);
	D3DXMatrixRotationZ(&modelRotZ, rotZ);
	D3DXMatrixMultiply(&modelRot, &modelRot, &modelRotZ);
	D3DXMatrixMultiply(&model, &model, &modelRot);

	//Setting the matrix of the camera
	D3DXMatrixTranslation( &matWorldTrans, newX, newY, newZ);
	D3DXMatrixRotationYawPitchRoll( &matWorldRot, newRY, newRX, 0);
	D3DXMatrixInverse( &matWorldRot, NULL, &matWorldRot);
	D3DXMatrixMultiply( &matCam, &matWorldTrans, &matWorldRot);

	//Multiply the modelmatrix + the CameraMatrix then set the transformation
	D3DXMatrixMultiply(&matWorld, &model, &matCam);
    device->SetTransform( D3DTS_WORLD, &matWorld );
}

/*
	Sets the view matrix
	@param x, the x position 
	@param y, the y position
	@param z, the z position
*/
void RendererDX9::SetupViewMatrix(float x, float y, float z)
{
	D3DXMATRIXA16 matView;
    
	D3DXVECTOR3 vEyePt(x, y, z); //camera location
    D3DXVECTOR3 vLookatPt(0.0f, 0.0f, 1.0f); //look at location
    D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f); // the up vector ( Y is up)

    D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookatPt, &vUpVec);
    device->SetTransform( D3DTS_VIEW, &matView );
}

/*
	Sets the projection matrix
*/
void RendererDX9::SetupProjectionMatrix()
{
	D3DXMATRIXA16 matProj;

    D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, 1.0f, 1.0f, 1000.0f);
	device->SetTransform(D3DTS_PROJECTION, &matProj);
}

/*
	Renders nonindexed triangles
	@param startVertex, The vertex where the device starts drawing
	@param numberOfTriangles, The quantity of triangles to be drawn
*/
void RendererDX9::DrawPrimitiveTriangle(int startVertex, int numberOfTriangles)
{
	this->device->DrawPrimitive(D3DPT_TRIANGLELIST, startVertex, numberOfTriangles);
}

/*
	Creates a vertexbuffer and adds it to the vertexBufferMap
	@param vertices, Contains all vertices that need to go in the vertex buffer
	@param numberOfVertices, The quantity of the vertices
*/
int RendererDX9::CreateVertexBuffer(ENGIE_VERTEX vertices[], int numberOfVertices)
{
	
	LPDIRECT3DVERTEXBUFFER9 VB = 0;
	
	this->device->CreateVertexBuffer(numberOfVertices * sizeof(ENGIE_VERTEX) ,
                                      0, D3DFVF_CUSTOMVERTEX,
                                      D3DPOOL_DEFAULT, &VB, NULL);

	VOID* pVertices;
    VB->Lock(0, sizeof( vertices ), ( void** )&pVertices, 0);
    memcpy(pVertices, vertices, sizeof( ENGIE_VERTEX ) * numberOfVertices);
    VB->Unlock();

	++ this->mapIndex;
	
	//Add the vertex buffer to the vertexBufferMap
	this->vertexBufferMap.insert(std::pair<int, LPDIRECT3DVERTEXBUFFER9>(mapIndex, VB));

	return this->mapIndex;
}

/*
	Sets a vertex buffer to a device data stream
	@param buffer, The index for the vertexBufferMap
	@param stride, Stride of the component, in bytes
*/
void RendererDX9::SetStreamSource(int buffer, int stride)
{ 
	LPDIRECT3DVERTEXBUFFER9 VB = this->vertexBufferMap[buffer];
	this->device->SetStreamSource(0, VB, 0, stride);
}

/*
	Renders a subset of a mesh
	@param model, Model object to get a DX9 mesh from
	@param i, Attribute id that specifies which subset from a mesh to draw
*/
void RendererDX9::DrawSubset(Model* model, DWORD i)
{
	LPD3DXMESH mesh = *model->GetMesh();
	mesh->DrawSubset(i);
}

/*
	Sets a texture
	@param texture, The texture that is to be set by the device
*/
void RendererDX9::SetTexture(Texture* texture)
{
	this->device->SetTexture(0, *texture->getTexture());
}

/*
	Sets a material
	@param model, Model object that has the materials
	@param materialIndex, Specifies which material we need to set
*/
void RendererDX9::SetMaterial(Model* model, int materialIndex)
{
	this->device->SetMaterial(&model->GetMaterials()[materialIndex]);
}

/*
	Sets the current vertex stream declaration
	@param fvf, DWORD containing the fixed function vertex type
*/
void RendererDX9::SetFvF(DWORD fvf)
{
	this->device->SetFVF(fvf);
}

/*
	Enables or disables z-buffering
	@param enable, true enables z-buffering, false disables z-buffering
*/
void RendererDX9::Zenable(bool enable)
{
	this->device->SetRenderState(D3DRS_ZENABLE, enable);
}