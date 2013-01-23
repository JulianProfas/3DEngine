#include "EntityCamera.h"

EntityCamera::EntityCamera(float posX, float posY, float posZ, float laX, float laY, float laZ)
	: Entity(posX, posY, posZ)
{
	lookAtX = laX;
	lookAtY = laY;
	lookAtZ = laZ;
}

EntityCamera::~EntityCamera()
{
}

void EntityCamera::SetCamera(Renderer* rd)
{
	//static_cast<RendererDX9*>(rd)->SetupViewMatrix(positionX, positionY, positionZ, lookAtX, lookAtY, lookAtZ);
}

void EntityCamera::SetLookAtX(float x)
{
	positionX = x;
}

float EntityCamera::GetLookAtX()
{
	return positionX;
}

void EntityCamera::SetLookAtY(float y)
{
	positionY = y;
}

float EntityCamera::GetLookAtY()
{
	return positionY;
}

void EntityCamera::SetLookAtZ(float z)
{
	positionZ = z;
}

float EntityCamera::GetLookAtZ()
{
	return positionZ;
}