#include "EntityModel.h"

EntityModel::EntityModel(float posX, float posY, float posZ, float rotX, float rotY, float rotZ, float scaX, float scaY, float scaZ, std::string mPath, std::string tPath, ResourcesManager* resMan)
	: Entity(posX, posY, posZ)
{
	rotationX = rotX;
	rotationY = rotY;
	rotationZ = rotZ;
	scaleX = scaX;
	scaleY = scaY;
	scaleZ = scaZ;
	m = &resMan->LoadModel(mPath);
	t = &resMan->LoadTexture(tPath);
}

EntityModel::~EntityModel()
{
}

void EntityModel::renderEntityModel(Renderer* rd)
{
	static_cast<RendererDX9*>(rd)->SetupWorldMatrix(positionX, positionY, positionZ, rotationX, rotationY, rotationZ, scaleX, scaleY, scaleZ);
	for( DWORD i = 0; i < m->GetNumMaterials(); i++)
	{
		// Set the material and texture for this subset
		static_cast<RendererDX9*>(rd)->SetMaterial(&m->GetMaterials()[i] );
		static_cast<RendererDX9*>(rd)->SetTexture(t->getTexture()[i]);
		// Draw the mesh subset
		static_cast<RendererDX9*>(rd)->DrawSubset(m->GetMesh(), i);
	}
}

void EntityModel::SetScaleX(float x)
{
	scaleX = x;
}

float EntityModel::GetScaleX()
{
	return scaleX;
}

void EntityModel::SetScaleY(float y)
{
	scaleY = y;
}

float EntityModel::GetScaleY()
{
	return scaleY;
}

void EntityModel::SetScaleZ(float z)
{
	scaleY = z;
}

float EntityModel::GetScaleZ()
{
	return scaleZ;
}

void EntityModel::Move(int d, float unit)
{
	if(d == 0)
	{
		this->positionZ -= unit;
	}
	else if(d == 1)
	{
		this->positionZ += unit;
	}
	else if(d == 2)
	{
		this->positionX += unit;
	}
	else if(d == 3)
	{
		this->positionX -= unit;
	}
	else if(d == 4)
	{
		this->positionY -= unit;
	}
	else if(d == 5)
	{
		this->positionY += unit;
	}
}