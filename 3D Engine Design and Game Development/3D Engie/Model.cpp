#include "Model.h"


Model::Model(LPD3DXMESH argMesh, std::string argName)
{
	mesh = argMesh;
	name = argName;
}


Model::~Model()
{
}

void* Model::GetMesh()
{
	return mesh;
}

void Model::SetMesh(void* argMesh)
{
	mesh = (LPD3DXMESH)argMesh;
}

std::string Model::GetName()
{
	return name;
}

void Model::SetName(std::string argName)
{
	name = argName;
}