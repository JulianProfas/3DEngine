#ifndef ENGIE_ENTITYMODEL_H
#define ENGIE_ENTITYMODEL_H

#include "Entity.h"
#include "ResourcesManager.h"
#include "RendererDX9.h"
#include "Model.h"
#include "Texture.h"

class EntityModel : public Entity
{
public:
	EntityModel(float posX, float posY, float posZ, float rotX, float rotY, float rotZ, float scaX, float scaY, float scaZ, std::string mPath, std::string tPath, ResourcesManager* resMan);
	~EntityModel();
	void renderEntityModel(RendererDX9* rdx9);
private:
	float scaleX;
	float scaleY;
	float scaleZ;
	Model* m;
	Texture* t;
};

#endif