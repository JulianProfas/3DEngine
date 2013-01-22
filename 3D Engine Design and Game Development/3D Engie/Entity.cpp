#include "Entity.h"

Entity::Entity(float posX, float posY, float posZ, float rotX, float rotY, float rotZ)
{
	positionX = posX;
	positionY = posY;
	positionZ = posZ;
	rotationX = rotX;
	rotationY = rotY;
	rotationZ = rotZ;
}

Entity::~Entity()
{
}

void Entity::SetPositionX(float x)
{
	positionX = x;
}

float Entity::GetPositionX()
{
	return positionX;
}

void Entity::SetPositionY(float y)
{
	positionY = y;
}

float Entity::GetPositionY()
{
	return positionY;
}

void Entity::SetPositionZ(float z)
{
	positionZ = z;
}

float Entity::GetPositionZ()
{
	return positionZ;
}

void Entity::SetRotationX(float x)
{
	rotationX = x;
}

float Entity::GetRotationX()
{
	return rotationX;
}

void Entity::SetRotationY(float y)
{
	rotationY = y;
}

float Entity::GetRotationY()
{
	return rotationY;
}

void Entity::SetRotationZ(float z)
{
	rotationZ = z;
}

float Entity::GetRotationZ()
{
	return rotationZ;
}