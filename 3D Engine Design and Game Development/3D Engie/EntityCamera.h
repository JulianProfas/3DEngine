#ifndef ENGIE_ENTITYCAMERA_H
#define ENGIE_ENTITYCAMERA_H

#include <d3dx9.h>
#include "Entity.h"
#include "ResourcesManager.h"
#include "Model.h"
#include "Texture.h"

class EntityCamera : public Entity
{
public:
	EntityCamera(float x, float y, float z);
	~EntityCamera();
	float GetPosX();
	float GetPosY();
	float GetPosZ();
	float GetPitch();
	float GetYaw();
	float GetRoll();
	void SetPitch(float pitch);
	void SetYaw(float yaw);
	void SetRoll(float roll);
	void MoveForward();
	void MoveBackward();
	void MoveLeft();
	void MoveRight();
	void MoveUp();
	void MoveDown();
private:
	float moveDistance;
	float yaw;                 // rotation around the y axis
	float pitch;               // rotation around the x axis
	float roll;                // rotation around the z axis
};

#endif