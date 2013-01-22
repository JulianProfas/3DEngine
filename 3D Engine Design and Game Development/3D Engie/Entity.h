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
	
	void SetPositionX(float x);
	float GetPositionX();
	void SetPositionY(float y);
	float GetPositionY();
	void SetPositionZ(float z);
	float GetPositionZ();
	void SetRotationX(float x);
	float GetRotationX();
	void SetRotationY(float y);
	float GetRotationY();
	void SetRotationZ(float z);
	float GetRotationZ();
protected:
	float positionX;
	float positionY;
	float positionZ;
	float rotationX;
	float rotationY;
	float rotationZ;
};

#endif