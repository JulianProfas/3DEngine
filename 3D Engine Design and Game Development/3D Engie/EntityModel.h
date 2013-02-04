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
	EntityModel(float posX, float posY, float posZ, float rotX, float rotY, float rotZ, float scaX, float scaY, float scaZ, std::string mPath, std::string tPath, ResourcesManager* resMan);
	~EntityModel();
	void renderEntityModel(Renderer* rd);
	void SetScaleX(float x);
	float GetScaleX();
	void SetScaleY(float y);
	float GetScaleY();
	void SetScaleZ(float z);
	float GetScaleZ();
	void Move(int d, float unit);
private:
	float rotationX;
	float rotationY;
	float rotationZ;
	float scaleX;
	float scaleY;
	float scaleZ;
	Model* m;
	Texture* t;
};

#endif