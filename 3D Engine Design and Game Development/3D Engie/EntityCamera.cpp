#include "EntityCamera.h"

/*
	Constructor for an EntityCamera
	@param x, the x position
	@param y, the y position
	@param z, the z position
*/
EntityCamera::EntityCamera(float x, float y, float z)
	: Entity(x, y, z)
{
	this->positionX = x;
	this->positionY = y;
	this->positionZ = z;
	this->moveDistance = 1.0f;
	this->yaw = 0.0f;
	this->pitch = 0.0f;
	this->roll = 0.0f;
}

/*
	Destructor for an EntityCamera object
*/
EntityCamera::~EntityCamera()
{

}

/*
	Get the x rotation
*/
float EntityCamera::GetPitch()
{
	return this->pitch;
}

/*
	Get the y rotation
*/
float EntityCamera::GetYaw()
{
	return this->yaw;
}

/*
	Get the z rotation
*/
float EntityCamera::GetRoll()
{
	return this->roll;
}

/*
	Set the x rotation
	@param pitch, new x rotation
*/
void EntityCamera::SetPitch(float pitch)
{
	this->pitch -= pitch;
}

/*
	Set the y rotation
	@param yaw, new y rortation
*/
void EntityCamera::SetYaw(float yaw)
{
	this->yaw -= yaw;
}

/*
	Set the x rotation
	@param roll, new z rotation
*/
void EntityCamera::SetRoll(float roll)
{
	this->roll += roll;
}

/*
	Moves the camera forward
*/
void EntityCamera::MoveForward()
{
	this->positionX -= this->moveDistance * sin(this->GetYaw());
	this->positionZ -= this->moveDistance * cos(this->GetYaw());
	this->positionY += this->moveDistance * sin(this->GetPitch());
}

/*
	Moves the camera backward
*/
void EntityCamera::MoveBackward()
{
	this->positionX += this->moveDistance * sin(this->GetYaw());
	this->positionZ += this->moveDistance * cos(this->GetYaw());
	this->positionY -= this->moveDistance * sin(this->GetPitch());
}

/*
	Moves the camera left
*/
void EntityCamera::MoveLeft()
{	
	this->positionX += this->moveDistance * cos(-this->GetYaw());
	this->positionZ += this->moveDistance * sin(-this->GetYaw());
}

/*
	Moves the camera right
*/
void EntityCamera::MoveRight()
{
	this->positionX -= this->moveDistance * cos(-this->GetYaw());
	this->positionZ -= this->moveDistance * sin(-this->GetYaw());
}

/*
	Moves the camera up
*/
void EntityCamera::MoveUp()
{
	this->positionY -= this->moveDistance;
}

/*
	Moves the camera down
*/
void EntityCamera::MoveDown()
{
	this->positionY += this->moveDistance;
}