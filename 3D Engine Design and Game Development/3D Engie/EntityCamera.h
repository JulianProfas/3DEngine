#ifndef ENGIE_ENTITYCAMERA_H
#define ENGIE_ENTITYCAMERA_H

#include "Entity.h"
#include "ResourcesManager.h"
#include "Renderer.h"
#include "RendererDX9.h"
#include "Model.h"
#include "Texture.h"

class EntityCamera : public Entity
{
public:
	EntityCamera(float posX, float posY, float posZ, float laX, float laY, float laZ);
	~EntityCamera();
	void SetCamera(Renderer* rd);
	void SetLookAtX(float x);
	float GetLookAtX();
	void SetLookAtY(float y);
	float GetLookAtY();
	void SetLookAtZ(float z);
	float GetLookAtZ();
private:
	float lookAtX;
	float lookAtY;
	float lookAtZ;
};

#endif