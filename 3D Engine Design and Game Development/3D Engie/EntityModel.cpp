#include "EntityModel.h"

/*
	Constructor for an EntityModel object
	@param posX, the x position
	@param posY, the y position
	@param posZ, the z position
	@param rotX, the x rotation
	@param rotY, the y rotation
	@param rotZ, the z rotation
	@param scaX, the x scaling
	@param scaY, the y scaling
	@param scaZ, the Z scaling
	@param modelPath, The URL to the model file
	@param texturePath, The URL to the texture file
*/
EntityModel::EntityModel(float posX, float posY, float posZ, float rotX, float rotY, float rotZ, float scaX, float scaY, float scaZ, std::string modelPath, std::string texturePath)
	: Entity(posX, posY, posZ)
{
	this->rotationX = rotX;
	this->rotationY = rotY;
	this->rotationZ = rotZ;
	this->scaleX = scaX;
	this->scaleY = scaY;
	this->scaleZ = scaZ;
	this->modelPath = modelPath;
	this->texturePath = texturePath;
}

/*
	Destructor for an EntityModel
*/
EntityModel::~EntityModel()
{

}

/*
	Renders the EntityModel
	@param renderer, Renderer object needed for rendering an EntityModel
*/
void EntityModel::renderEntityModel(Renderer* renderer, EntityCamera* camera)
{
	renderer->SetupWorldMatrix(positionX, positionY, positionZ, rotationX, rotationY, rotationZ, scaleX, scaleY, scaleZ, camera);
	
	for(DWORD i = 0; i < *model->GetNumMaterials(); ++i)
	{
		// Set the material and texture for this subset
		renderer->SetMaterial(this->model, i);
		renderer->SetTexture(this->texture);
		// Draw the mesh subset
		renderer->DrawSubset(this->model, i);
	}
}

void EntityModel::SetScaleX(float x)
{
	this->scaleX = x;
}

float EntityModel::GetScaleX()
{
	return scaleX;
}

void EntityModel::SetScaleY(float y)
{
	this->scaleY = y;
}

float EntityModel::GetScaleY()
{
	return scaleY;
}

void EntityModel::SetScaleZ(float z)
{
	this->scaleY = z;
}

float EntityModel::GetScaleZ()
{
	return scaleZ;
}

/*
	Loads the resources needed by this object
	@param resourceManager, ResourcesManager object for managing the loaded resources
	@param renderer, Renderer object for loading the resources
*/
void EntityModel::LoadResources(ResourcesManager* resourceManager, Renderer* renderer)
{
	this->model = resourceManager->LoadModel(renderer->GetDevice(), this->modelPath);
	this->texture = resourceManager->LoadTexture(renderer->GetDevice(), this->texturePath);
}