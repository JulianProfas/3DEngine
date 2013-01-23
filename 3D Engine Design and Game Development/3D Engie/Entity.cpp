#include "Entity.h"

Entity::Entity(float posX, float posY, float posZ)
{
	positionX = posX;
	positionY = posY;
	positionZ = posZ;
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