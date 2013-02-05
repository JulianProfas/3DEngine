#ifndef ENGIE_ENTITYMODEL_H
#define ENGIE_ENTITYMODEL_H

#include "Entity.h"
#include "ResourcesManager.h"
#include "Renderer.h"
#include "Model.h"
#include "Texture.h"

class EntityModel : public Entity
{
public:
	//Constructor for an EntityModel object
	EntityModel(float posX, float posY, float posZ, float rotX, float rotY, float rotZ, float scaX, float scaY, float scaZ, std::string modelPath, std::string texturePath);
	//Destructor for an EntityModel object
	~EntityModel();
	//Renders the EntityModel
	void renderEntityModel(Renderer* renderer);
	//Set the x scale
	void SetScaleX(float x);
	//Get the x scale
	float GetScaleX();
	//Set the y scale
	void SetScaleY(float y);
	//Get the y scale
	float GetScaleY();
	//Set the z scale
	void SetScaleZ(float z);
	//Get the z scale
	float GetScaleZ();
	//Loads the resources needed by this object
	void LoadResources(ResourcesManager* resourceManager, Renderer* renderer);
private:
	//x rotation
	float rotationX;
	//y rotation
	float rotationY;
	//z rotation
	float rotationZ;
	//x scaling
	float scaleX;
	//y scaling
	float scaleY;
	//z scaling
	float scaleZ;
	//The URL to the model file
	std::string modelPath;
	//The URL to the texture file
	std::string texturePath;
	//Model object needed to render this object
	Model* model;
	//Texture object needed to render this object
	Texture* texture;
};

#endif