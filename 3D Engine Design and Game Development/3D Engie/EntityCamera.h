#ifndef ENGIE_ENTITYCAMERA_H
#define ENGIE_ENTITYCAMERA_H

#include "Entity.h"
#include "math.h"

class EntityCamera : public Entity
{
public:
	//Constructor for an EntityCamera object
	EntityCamera(float x, float y, float z);
	//Destructor for an EntityCamera object
	~EntityCamera();
	//Get x rotation
	float GetPitch();
	//Get y rotation
	float GetYaw();
	//Get Z rotaion
	float GetRoll();
	//Set the x rotation
	void SetPitch(float pitch);
	//Set the y rotation
	void SetYaw(float yaw);
	//Set the z rotation
	void SetRoll(float roll);
	//Move the camera forward
	void MoveForward();
	//Move the camera backward
	void MoveBackward();
	//Move the camera to the left
	void MoveLeft();
	//Move the camera to the right
	void MoveRight();
	//Move the camera up
	void MoveUp();
	//Move the camera down
	void MoveDown();

private:
	//The move distance of the camera
	float moveDistance;
	//The x rotation
	float pitch; 
	//The Y rotation
	float yaw;                 
	//The z rotation             
	float roll;              
};

#endif