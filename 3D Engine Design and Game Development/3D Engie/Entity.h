#ifndef ENGIE_ENTITY_H
#define ENGIE_ENTITY_H

#include <string>
#include <d3dx9.h>
#include <d3d9.h>

class Entity
{
public:
	Entity(float posX, float posY, float posZ, float rotX, float rotY, float rotZ);
	~Entity();
	float positionX;
	float positionY;
	float positionZ;
	float rotationX;
	float rotationY;
	float rotationZ;
	float GetPositionX();
	float GetPositionY();
	float GetPositionZ();
private:
	
};

#endif