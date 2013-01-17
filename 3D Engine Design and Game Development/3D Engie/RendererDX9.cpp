#include "RendererDX9.h"

RendererDX9::RendererDX9()
{
	this->g_pD3D = NULL; 
	this->g_pd3dDevice = NULL;
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

//-----------------------------------------------------------------------------
// Name: Cleanup()
// Desc: Releases all previously initialized objects
//-----------------------------------------------------------------------------
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

void RendererDX9::PresentScene()
{
    // Present the backbuffer contents to the display
    g_pd3dDevice->Present( NULL, NULL, NULL, NULL );
}


//-----------------------------------------------------------------------------
// Name: Render()
// Desc: Draws the scene
//-----------------------------------------------------------------------------
VOID RendererDX9::Render(Model* m, Texture* t)
{
    
}

void* RendererDX9::GetDevice()
{
	return this->g_pd3dDevice;
}

/*!
 * \brief
 * Set where a object should be rendered in the world
 * 
 * \param x
 * Location on X-axis
 * 
 * \param y
 * Location on Y-axis
 * 
 * \param z
 * Location on Z-Axis
 * 
 * \param rotX
 * Rotation on X-Axis
 * 
 * \param rotY
 * Rotation on Y-Axis
 * 
 * \param rotZ
 * Rotation on Z-Axis
 * 
 * \param scaleX
 * Scaling on X-Axis
 * 
 * \param scaleY
 * Scaling on Y-Axis
 * 
 * \param scaleZ
 * Scaling on Z-axis
 * 
 * \param camera
 * Pointer to the camera
 * 
 * Setup the location, scaling and rotation of an object, then multiply it with the matrix of the camera.
 * 
 */
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


void RendererDX9::SetupViewMatrix()
{
	D3DXMATRIXA16 matView;

	D3DXVECTOR3 vEyePt( 0.0f, 25.0f, -128.0f ); //camera location
    D3DXVECTOR3 vLookatPt( 0.0f, 0.0f, 0.0f ); //look at location
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
	g_pd3dDevice->DrawPrimitive(PrimitiveType, StartVertex, NumberOfPrimitives);
}

LPDIRECT3DVERTEXBUFFER9 RendererDX9::CreateVertexBuffer(ENGIE_VERTEX Vertices[], int NumberofVertices)
{
	int tail = 0;
	LPDIRECT3DVERTEXBUFFER9 VB = 0;
	
	g_pd3dDevice->CreateVertexBuffer( NumberofVertices * sizeof(ENGIE_VERTEX) ,
                                      0, D3DFVF_CUSTOMVERTEX,
                                      D3DPOOL_DEFAULT, &VB, NULL );

	VOID* pVertices;
    VB->Lock( 0, sizeof( Vertices ), ( void** )&pVertices, 0 );
    memcpy( pVertices, Vertices, sizeof( ENGIE_VERTEX ) * NumberofVertices );
    VB->Unlock();
	return VB;
}

void RendererDX9::SetStreamSource(LPDIRECT3DVERTEXBUFFER9 buffer, unsigned int Stride)
{ 
	g_pd3dDevice->SetStreamSource( 0, buffer, 0, Stride );
}

void RendererDX9::DrawSubset(LPD3DXMESH Mesh, DWORD i)
{
	Mesh->DrawSubset(i);
}

void RendererDX9::SetMaterial(D3DMATERIAL9 *MeshMaterial)
{
	g_pd3dDevice->SetMaterial(MeshMaterial);
}

void RendererDX9::SetTexture(LPDIRECT3DTEXTURE9 Texture)
{
	g_pd3dDevice->SetTexture( 0, Texture);
}