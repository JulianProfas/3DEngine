#include "Model.h"

/*
	Constructor for a Model object
	@param device, Model needs a device to load a mesh from it
	@param filePath, the URL to the modelfile
*/
Model::Model(LPDIRECT3DDEVICE9 device, std::string filePath)
{
	//initialize attributes
	mesh = NULL;
	materials = NULL;
	numMaterials = 0;
	//loads the mesh from the filePath
	LoadMesh(device, filePath);	
}

/*
	Destructor for a Model object
*/
Model::~Model()
{

}

/*
	Get the directx 9 mesh
*/
LPD3DXMESH* Model::GetMesh()
{
	return this->mesh;
}

/*
	Get the directx 9 materials
*/
D3DMATERIAL9* Model::GetMaterials()
{
	return this->materials;
}

/*
	Get the number of materials
*/
DWORD* Model::GetNumMaterials()
{
	return this->numMaterials;
}

/*
	Loads the directx 9 mesh from the given filePath
	@param device, a device is needed to load the mesh
	@param filePath, the URL to the modelfile
*/
void Model::LoadMesh(LPDIRECT3DDEVICE9 device, std::string filePath)
{
	LPD3DXBUFFER pD3DXMtrlBuffer = NULL;
	LPCSTR path = filePath.c_str();
	HRESULT res;

	//Load the mesh from the specified file
	res = D3DXLoadMeshFromX(
		path,
		D3DXMESH_SYSTEMMEM,
		device,
		NULL,
		&pD3DXMtrlBuffer,
		NULL,
		this->numMaterials,
		this->mesh);

	if(FAILED(res))
	{
		//Failed loading model
		Logger::GetInstance()->Write("Failed loading model: " + filePath);
	}
	else
	{
		D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();
		
		this->materials = new D3DMATERIAL9[*this->numMaterials];		
		
		for (DWORD i = 0; i < *this->numMaterials; i++)
		{
			this->materials[i] = d3dxMaterials[i].MatD3D;
			this->materials[i].Ambient = this->materials[i].Diffuse;
		}

		//Release the materialbuffer
		pD3DXMtrlBuffer->Release();

		Logger::GetInstance()->Write("Successfully loaded model: " + filePath);
	}
}