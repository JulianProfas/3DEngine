#include "EntityCamera.h"

EntityCamera::EntityCamera(float x, float y, float z)
	: Entity(x, y, z)
{
	positionX = x;
	positionY = y;
	positionZ = z;
	moveDistance = 1.0f;
	yaw = 0.0f;
	pitch = 0.0f;
	roll = 0.0f;
}

EntityCamera::~EntityCamera()
{
}

/*!
 * \brief
 * Returns X position
 * 
 * \returns
 * float
 * 
 * Gives the X position of the camera
 * 
 */
float EntityCamera::GetPosX()
{
	return this->positionX;
}

/*!
 * \brief
 * Returns Y position
 * 
 * \returns
 * float
 * 
 * Gives the Y position of the camera
 * 
 */
float EntityCamera::GetPosY()
{
	return this->positionY;
}

/*!
 * \brief
 * Returns Z position
 * 
 * \returns
 * float
 * 
 * Gives the Z position of the camera
 * 
 */
float EntityCamera::GetPosZ()
{
	return this->positionZ;
}

/*!
 * \brief
 * Returns X rotation
 * 
 * \returns
 * float
 * 
 * Gives the X rotation of the camera
 * 
 */
float EntityCamera::GetPitch()
{
	return this->pitch;
}

/*!
 * \brief
 * Returns Y rotation
 * 
 * \returns
 * float
 * 
 * Gives the Y rotation of the camera
 * 
 */
float EntityCamera::GetYaw()
{
	return this->yaw;
}

/*!
 * \brief
 * Returns Z rotation
 * 
 * \returns
 * float
 * 
 * Gives the Z rotation of the camera
 * 
 */
float EntityCamera::GetRoll()
{
	return this->roll;
}

/*!
 * \brief
 * Set the X rotation
 * 
 * \param rotX
 * the new X rotation
 * 
 * This function sets the X rotation for the camera when it changes
 * 
 */
void EntityCamera::SetPitch(float pitch)
{
	this->pitch -= pitch;
}

/*!
 * \brief
 * Set the Y rotation
 * 
 * \param rotY
 * the new Y rotation
 * 
 * This function sets the Y rotation for the camera when it changes
 * 
 */
void EntityCamera::SetYaw(float yaw)
{
	this->yaw -= yaw;
}

/*!
 * \brief
 * Set the Z rotation
 * 
 * \param rotZ
 * the new Z rotation
 * 
 * This function sets the Z rotation for the camera when it changes
 * 
 */
void EntityCamera::SetRoll(float roll)
{
	this->roll += roll;
}

/*!
 * \brief
 * Move the Camera forward
 * 
 * This function makes the camera move forward in the world
 * 
 */
void EntityCamera::MoveForward()
{
	this->positionX -= this->moveDistance * sin(this->GetYaw());
	this->positionZ -= this->moveDistance * cos(this->GetYaw());
	this->positionY += this->moveDistance * sin(this->GetPitch());
}

/*!
 * \brief
 * Move the Camera backward
 * 
 * This function makes the camera move backward in the world
 * 
 */
void EntityCamera::MoveBackward()
{
	this->positionX += this->moveDistance * sin(this->GetYaw());
	this->positionZ += this->moveDistance * cos(this->GetYaw());
	this->positionY -= this->moveDistance * sin(this->GetPitch());
}

/*!
 * \brief
 * Move the Camera left
 * 
 * This function makes the camera move left in the world
 * 
 */
void EntityCamera::MoveLeft()
{	
	this->positionX += this->moveDistance * cos(-this->GetYaw());
	this->positionZ += this->moveDistance * sin(-this->GetYaw());
}

/*!
 * \brief
 * Move the Camera right
 * 
 * This function makes the camera move right in the world
 * 
 */
void EntityCamera::MoveRight()
{
	this->positionX -= this->moveDistance * cos(-this->GetYaw());
	this->positionZ -= this->moveDistance * sin(-this->GetYaw());
}

/*!
 * \brief
 * Move the Camera up
 * 
 * This function makes the camera move up in the world
 * 
 */
void EntityCamera::MoveUp()
{
	this->positionY -= this->moveDistance;
}

/*!
 * \brief
 * Move the Camera down
 * 
 * This function makes the camera move down in the world
 * 
 */
void EntityCamera::MoveDown()
{
	this->positionY += this->moveDistance;
}