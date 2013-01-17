#include "EntityModel.h"

EntityModel::EntityModel(float posX, float posY, float posZ, float rotX, float rotY, float rotZ, float scaX, float scaY, float scaZ, std::string mPath, std::string tPath, ResourcesManager* resMan)
	: Entity(posX, posY, posZ, rotX, rotY, rotZ)
{
	scaleX = scaX;
	scaleY = scaY;
	scaleZ = scaZ;
	m = &resMan->LoadModel(mPath);
	t = &resMan->LoadTexture(tPath);
}

EntityModel::~EntityModel()
{
}

void EntityModel::renderEntityModel(RendererDX9* rdx9)
{
	rdx9->SetupWorldMatrix(positionX, positionY, positionZ, rotationX, rotationY, rotationZ, scaleX, scaleY, scaleZ);
	for( DWORD i = 0; i < m->GetNumMaterials(); i++)
	{
		// Set the material and texture for this subset
		rdx9->SetMaterial(&m->GetMaterials()[i] );
		rdx9->SetTexture(t->getTexture()[i]);
		// Draw the mesh subset
		rdx9->DrawSubset(m->GetMesh(), i);
	}
}

