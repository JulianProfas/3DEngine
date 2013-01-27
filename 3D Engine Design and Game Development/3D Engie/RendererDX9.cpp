#include "RendererDX9.h"

RendererDX9::RendererDX9()
{
	this->g_pD3D = NULL; 
	this->g_pd3dDevice = NULL;
	this->mapIndex = 0;
}

HRESULT RendererDX9::InitDevice(HWND hWnd, int width, int height)
{
	// Create the D3D object.
    if( NULL == ( g_pD3D = Direct3DCreate9( D3D_SDK_VERSION ) ) )
        return E_FAIL;

	D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory( &d3dpp, sizeof( d3dpp ) );
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	if( FAILED( g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
                                      D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                                      &d3dpp, &g_pd3dDevice ) ) )
    {
        return E_FAIL;
    }

    // Device state would normally be set here
	// Turn on the zbuffer

    // Turn on ambient lighting 
	g_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);	//Counter Clockwise Cullmode
	g_pd3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE ); //No lightning
    g_pd3dDevice->SetRenderState( D3DRS_ZENABLE, TRUE ); //Z buffer on
	g_pd3dDevice->SetRenderState(D3DRS_AMBIENT, 0xffffffff ); //Ambient is white
	g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true ); //Turn Alphablending on
	g_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA ); //Type alphablending
	g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA); //Type alphablending

    return S_OK;
}


VOID RendererDX9::CleanUp()
{
    if( g_pd3dDevice != NULL )
        g_pd3dDevice->Release();

    if( g_pD3D != NULL )
        g_pD3D->Release();
}

void RendererDX9::ClearScene()
{
	 // Clear the backbuffer to a blue color
    g_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB( 0, 0, 255 ), 1.0f, 0 );
	// Clear the z buffer
	g_pd3dDevice->Clear( 0, NULL, D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB( 0, 0, 255 ), 1.0f, 0 );
}

bool RendererDX9::BeginScene()
{
	if( NULL == g_pd3dDevice )
        return false;
	
	 // Begin the scene
    if(SUCCEEDED( g_pd3dDevice->BeginScene()))
    {
		return true;
	}
	return false;
}

void RendererDX9::EndScene()
{	
     // End the scene
     g_pd3dDevice->EndScene();
}

/*
	Present the backbuffer contents to the display
*/
void RendererDX9::PresentScene(HWND hWnd)
{
    g_pd3dDevice->Present( NULL, NULL, hWnd, NULL );
}

void* RendererDX9::GetDevice()
{
	return this->g_pd3dDevice;
}

void RendererDX9::SetupWorldMatrix(float x, float y, float z, float rotX, float rotY, float rotZ, float scaleX, float scaleY, float scaleZ)
{
	//The Matrix variables
	D3DXMATRIXA16 matWorld;
	D3DXMATRIXA16 matWorldTrans;
	D3DXMATRIXA16 matWorldRot;
	D3DXMATRIXA16 matWorldScale;

	D3DXMatrixScaling(&matWorldScale, scaleX, scaleY, scaleZ);
	D3DXMatrixRotationYawPitchRoll(&matWorldRot, rotX, rotY, rotZ);
	D3DXMatrixTranslation(&matWorldTrans, x, y, z);

	D3DXMatrixMultiply(&matWorld, &matWorldScale, &matWorldTrans);
	D3DXMatrixMultiply(&matWorld, &matWorldRot, &matWorld);

	//Multiply the modelmatrix + the CameraMatrix then set the transformation
    g_pd3dDevice->SetTransform(D3DTS_WORLD, &matWorld );
}


void RendererDX9::SetupViewMatrix(float x, float y, float z, float laX, float laY, float laZ)
{
	D3DXMATRIXA16 matView;

	/*D3DXVECTOR3 vEyePt( 0.0f, 25.0f, -128.0f ); //camera location
    D3DXVECTOR3 vLookatPt( 0.0f, 0.0f, 0.0f ); //look at location
    D3DXVECTOR3 vUpVec( 0.0f, 1.0f, 0.0f ); // the up vector ( Y is up)
    */
	D3DXVECTOR3 vEyePt(x, y, z); //camera location
    D3DXVECTOR3 vLookatPt(laX, laY, laZ); //look at location
    D3DXVECTOR3 vUpVec( 0.0f, 1.0f, 0.0f ); // the up vector ( Y is up)

    D3DXMatrixLookAtLH( &matView, &vEyePt, &vLookatPt, &vUpVec );
    g_pd3dDevice->SetTransform( D3DTS_VIEW, &matView );
}

void RendererDX9::SetupProjectionMatrix()
{
	D3DXMATRIXA16 matProj;

    D3DXMatrixPerspectiveFovLH( &matProj, D3DX_PI / 4, 1.0f, 1.0f, 1000.0f );
    g_pd3dDevice->SetTransform( D3DTS_PROJECTION, &matProj );
}


void RendererDX9::DrawPrimitive(D3DPRIMITIVETYPE PrimitiveType, unsigned int StartVertex, unsigned int NumberOfPrimitives)
{
	this->g_pd3dDevice->DrawPrimitive(PrimitiveType, StartVertex, NumberOfPrimitives);
}

int RendererDX9::CreateVertexBuffer(ENGIE_VERTEX Vertices[], int NumberofVertices)
{
	
	LPDIRECT3DVERTEXBUFFER9 VB = 0;
	
	g_pd3dDevice->CreateVertexBuffer( NumberofVertices * sizeof(ENGIE_VERTEX) ,
                                      0, D3DFVF_CUSTOMVERTEX,
                                      D3DPOOL_DEFAULT, &VB, NULL );

	VOID* pVertices;
    VB->Lock( 0, sizeof( Vertices ), ( void** )&pVertices, 0 );
    memcpy( pVertices, Vertices, sizeof( ENGIE_VERTEX ) * NumberofVertices );
    VB->Unlock();

	++ this->mapIndex;

	this->VBM.insert(std::pair<int, LPDIRECT3DVERTEXBUFFER9>(mapIndex, VB));

	return mapIndex;
}

void RendererDX9::SetStreamSource(int buffer, unsigned int Stride)
{ 
	LPDIRECT3DVERTEXBUFFER9 VB = VBM[buffer];
	this->g_pd3dDevice->SetStreamSource(0, VB, 0, Stride);
}

void RendererDX9::DrawSubset(LPD3DXMESH Mesh, DWORD i)
{
	Mesh->DrawSubset(i);
}

void RendererDX9::SetMaterial(D3DMATERIAL9 *MeshMaterial)
{
	this->g_pd3dDevice->SetMaterial(MeshMaterial);
}

void RendererDX9::SetTexture(LPDIRECT3DTEXTURE9 Texture)
{
	this->g_pd3dDevice->SetTexture( 0, Texture);
}

void RendererDX9::SetFvF(DWORD fvf)
{
	this->g_pd3dDevice->SetFVF(fvf);
}

void RendererDX9::Zenable(bool enable)
{
	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, enable);
}