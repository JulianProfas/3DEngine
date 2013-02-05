#ifndef ENGIE_MODEL_H
#define ENGIE_MODEL_H

#include <string>
#include <d3dx9.h>
#include <d3d9.h>
#include "Logger.h"
#include <dxerr.h>

class Model
{
public:
	//Constructor for a Model object
	Model(void* device, std::string filePath);
	//Destructor for a Model object
	~Model();
	//Get the Mesh 
	LPD3DXMESH* GetMesh();
	//Get the number of materials
	DWORD* GetNumMaterials();
	//Get the materials
	D3DMATERIAL9* GetMaterials();

private:
	//Loads the mesh from the given filePath
	void LoadMesh(void* device, std::string filePath);
	
	//Directx 9 Mesh
	LPD3DXMESH mesh;
	//The number of materials in the mesh
	DWORD numMaterials;
	//The materials in the mesh
	D3DMATERIAL9* materials;
};

#endif