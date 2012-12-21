#ifndef ENGIE_MODEL_H
#define ENGIE_MODEL_H

#include <string>
#include <d3dx9.h>
#include <d3d9.h>
#include "Logger.h"
#include <strsafe.h>
#include <Windows.h>
#include <mmsystem.h>

class Model
{
public:
	Model(LPDIRECT3DDEVICE9 g_pd3dDevice, std::string pathName);
	~Model();
	std::string* GetPathName();
	LPD3DXMESH GetMesh();
	DWORD GetNumMaterials();
	D3DMATERIAL9* GetMaterials();
private:
	LPD3DXMESH mesh;
	std::string* pathName;
	DWORD numMaterials;
	D3DMATERIAL9* materials;
	void LoadMesh(LPDIRECT3DDEVICE9 g_pd3dDevice);
};

#endif