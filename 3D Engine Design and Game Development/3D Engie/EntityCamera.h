#ifndef ENGIE_ENTITYCAMERA_H
#define ENGIE_ENTITYCAMERA_H

#include <d3dx9.h>
#include "Entity.h"
#include "ResourcesManager.h"
#include "Renderer.h"
#include "RendererDX9.h"
#include "Model.h"
#include "Texture.h"
#define DEGTORAD(degree) ((D3DX_PI / 180.0f) * (degree)) // converts from degrees to radians

struct ViewMatrix{
float _11, _12, _13, _14;
float _21, _22, _23, _24;
float _31, _32, _33, _34;
float _41, _42, _43, _44;
};

class EntityCamera : public Entity
{
public:
	EntityCamera(float x, float y, float z);
	~EntityCamera();
	void Yaw(float amount);
	void Pitch(float amount);
	void CalculateViewMatrix(Renderer* rd);
private:
	D3DXVECTOR3 position;      // camera position
	float yaw;                 // rotation around the y axis
	float pitch;               // rotation around the x axis
	float roll;                // rotation around the z axis
	D3DXVECTOR3 up,look,right; // camera axis
};

#endif