#ifndef ENGIE_ENTITY_H
#define ENGIE_ENTITY_H

#include <string>
#include <d3dx9.h>
#include <d3d9.h>

class Entity
{
public:
	Entity(float posX, float posY, float posZ);
	~Entity();
	
	void SetPositionX(float x);
	float GetPositionX();
	void SetPositionY(float y);
	float GetPositionY();
	void SetPositionZ(float z);
	float GetPositionZ();
protected:
	float positionX;
	float positionY;
	float positionZ;
};

#endif