#include "EntityCamera.h"

EntityCamera::EntityCamera(float x, float y, float z)
	: Entity(x, y, z)
{
	up = D3DXVECTOR3(0.0f,1.0f,0.0f);
	look = D3DXVECTOR3(0.0f,0.0f,1.0f);
	right = D3DXVECTOR3(1.0f,0.0f,0.0f);
	position = D3DXVECTOR3(x, y, z);
	yaw = 0;
	pitch = 0;
	roll = 0;
}

EntityCamera::~EntityCamera()
{
}

void EntityCamera::CalculateViewMatrix(Renderer* rd)
{
  up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
  look = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
  right = D3DXVECTOR3(1.0f, 0.0f, 0.0f);

  D3DXMATRIX yawMatrix;
  D3DXMatrixRotationAxis(&yawMatrix, &up, yaw); 

  D3DXVec3TransformCoord(&look, &look, &yawMatrix);
  D3DXVec3TransformCoord(&right, &right, &yawMatrix);

  D3DXMATRIX pitchMatrix;
  D3DXMatrixRotationAxis(&pitchMatrix, &right, pitch);

  D3DXVec3TransformCoord(&look, &look, &pitchMatrix);
  D3DXVec3TransformCoord(&up, &up, &pitchMatrix);

  D3DXMATRIX rollMatrix;
  D3DXMatrixRotationAxis(&rollMatrix, &look, roll);

  D3DXVec3TransformCoord(&right, &right, &rollMatrix);
  D3DXVec3TransformCoord(&up, &up, &rollMatrix);

  D3DXMATRIX viewMatrix;
  D3DXMatrixIdentity(&viewMatrix);
  viewMatrix._11 = right.x; viewMatrix._12 = up.x; viewMatrix._13 = look.x;
  viewMatrix._21 = right.y; viewMatrix._22 = up.y; viewMatrix._23 = look.y;
  viewMatrix._31 = right.z; viewMatrix._32 = up.z; viewMatrix._33 = look.z;

  viewMatrix._41 = - D3DXVec3Dot( &position, &right );
  viewMatrix._42 = - D3DXVec3Dot( &position, &up );
  viewMatrix._43 = - D3DXVec3Dot( &position, &look );

  static_cast<RendererDX9*>(rd)->SetupViewMatrix(viewMatrix);
}

void EntityCamera::Yaw(float amount)
{
   yaw += DEGTORAD(amount);
}

void EntityCamera::Pitch(float amount)
{
   pitch += DEGTORAD(amount);
}