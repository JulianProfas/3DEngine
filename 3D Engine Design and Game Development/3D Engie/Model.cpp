#include "Model.h"

/*

*/
Model::Model(LPDIRECT3DDEVICE9 g_pd3dDevice, std::string pathName)
{
	this->pathName = &pathName;
	this->mesh = NULL;
	this->materials = NULL;
	this->numMaterials = 0L;
	this->LoadMesh(g_pd3dDevice, pathName);
	
}

/*

*/
Model::~Model()
{

}

/*

*/
std::string* Model::GetPathName()
{
	return this->pathName;
}

/*

*/
LPD3DXMESH Model::GetMesh()
{
	return this->mesh;
}

/*

*/
D3DMATERIAL9* Model::GetMaterials()
{
	return this->materials;
}

/*

*/
DWORD Model::GetNumMaterials()
{
	return this->numMaterials;
}

/*

*/
void Model::LoadMesh(LPDIRECT3DDEVICE9 g_pd3dDevice, std::string filePath)
{
	LPD3DXBUFFER pD3DXMtrlBuffer = NULL;
	LPCSTR path = filePath.c_str();

	// Load the mesh from the specified file
	if (FAILED(D3DXLoadMeshFromX(
		path,
		D3DXMESH_SYSTEMMEM,
		g_pd3dDevice,
		NULL,
		&pD3DXMtrlBuffer,
		NULL,
		&this->numMaterials,
		&this->mesh)))
	{
		// Failed loading model
		Logger::GetInstance()->Write("Failed loading model");
    }
	else
	{
		D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();
		
		this->materials = new D3DMATERIAL9[this->numMaterials];		
		
		for (DWORD i = 0; i < this->numMaterials; i++)
		{
			this->materials[i] = d3dxMaterials[i].MatD3D;
			this->materials[i].Ambient = this->materials[i].Diffuse;
		}

		pD3DXMtrlBuffer->Release();
		Logger::GetInstance()->Write("Successful loaded model");
	}
}