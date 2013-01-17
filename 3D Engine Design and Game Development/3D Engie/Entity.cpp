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

