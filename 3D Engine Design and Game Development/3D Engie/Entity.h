#ifndef ENGIE_ENTITY_H
#define ENGIE_ENTITY_H



class Entity
{
public:
	//Constructor for an Entity object
	Entity(float posX, float posY, float posZ);
	//Destructor for an Entity object
	~Entity();
	//Set x position
	void SetPositionX(float x);
	//Get x position
	float GetPositionX();
	//Set y position
	void SetPositionY(float y);
	//Get y position
	float GetPositionY();
	//Set z position
	void SetPositionZ(float z);
	//Get z position
	float GetPositionZ();

protected:
	//The x position
	float positionX;
	//The y position
	float positionY;
	//The z position
	float positionZ;
};

#endif