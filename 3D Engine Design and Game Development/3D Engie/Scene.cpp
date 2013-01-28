#include "Scene.h"

Scene::Scene(Renderer* r, ResourcesManager* rm, std::string sceneName)
{
	this->sceneRenderer  = r;
	this->resourceManager = rm;
	this->sceneName = sceneName;
	this->sceneEntitys = new std::list<EntityModel>();
	this->LoadScene(sceneName);
}

Scene::~Scene()
{

}

void Scene::LoadScene(std::string sceneName)
{
	Logger::GetInstance()->Write("Loading scene " + sceneName);
	
	std::ifstream fileStream(sceneName);

	if(fileStream.good())
	{
		while(!fileStream.eof())
		{
			std::string line;
			std::getline(fileStream, line);

			if(line.compare("Camera:") == 0) // 0 means that the two strings match
			{
				float posX, posY, posZ;
				fileStream >> posX >> posY >> posZ;
				this->sceneCamera = new EntityCamera(posX, posY, posZ);
			}
			else if(line.compare("SkyBox:") == 0)
			{
				std::string front, back, left, right, top, bottom;
				fileStream >> front >> back >> left >> right >> top >> bottom;
				std::vector<Texture*> textures;
				std::vector<Texture*>::iterator its; 
				its = textures.begin();
				its = textures.insert(its, &this->resourceManager->LoadTexture(front));
				its = textures.insert(its, &this->resourceManager->LoadTexture(back));
				its = textures.insert(its, &this->resourceManager->LoadTexture(left));
				its = textures.insert(its, &this->resourceManager->LoadTexture(right));
				its = textures.insert(its, &this->resourceManager->LoadTexture(top));
				its = textures.insert(its, &this->resourceManager->LoadTexture(bottom));
	
				this->sceneSky = new SkyBox(this->sceneRenderer, textures);
			}
			else if(line.compare("Terrain:") == 0)
			{
				std::string heightMap;
				std::string terrainTexture;

				fileStream >> heightMap >> terrainTexture;

				this->sceneTerrain = new Terrain(heightMap, terrainTexture, this->sceneRenderer, this->resourceManager);
			}
			else if(line.compare("Entity:") == 0)
			{
				float posX, posY, posZ, rotX, rotY, rotZ, scaX, scaY, scaZ;
				std::string modelPath;
				std::string texturePath;

				fileStream >> posX >> posY >> posZ >> rotX >> rotY >> rotZ >> scaX >> scaY >> scaZ >> modelPath >> texturePath;
				
				EntityModel* e = new EntityModel(posX, posY, posZ, rotX, rotY, rotZ, scaX, scaY, scaZ, modelPath, texturePath, this->resourceManager);
				this->sceneEntitys->push_back(*e);
			}
		}
		Logger::GetInstance()->Write("Scene " + sceneName + " loaded");
	}
	else
	{
		Logger::GetInstance()->Write("can't open scene file: " + sceneName);
	}
}

/*
	Renders the scene to the window
*/
void Scene::RenderScene(HWND hWnd)
{
	this->sceneRenderer->ClearScene();
	this->sceneRenderer->BeginScene();
	this->sceneRenderer->SetupProjectionMatrix();
	//this->sceneRenderer->SetupViewMatrix();
	this->sceneCamera->CalculateViewMatrix(this->sceneRenderer);

	// render sky
	this->sceneRenderer->Zenable(false);
	this->sceneSky->Render(this->sceneRenderer, this->sceneCamera);

	// render terrain
	this->sceneRenderer->Zenable(true);
	this->sceneTerrain->RenderTerrain(this->sceneRenderer);

	// render entitys
	for(EntityList::iterator i = this->sceneEntitys->begin(); i != this->sceneEntitys->end(); ++i)
	{
		i->renderEntityModel(this->sceneRenderer);
	}

	this->sceneRenderer->EndScene();
	this->sceneRenderer->PresentScene(hWnd);

}

void Scene::Move(int d, float z)
{
	this->sceneTerrain->Move(d, z);
	for(EntityList::iterator i = this->sceneEntitys->begin(); i != this->sceneEntitys->end(); ++i)
	{
		i->Move(d, z);
	}
}

EntityCamera* Scene::GetCamera()
{
	return this->sceneCamera;
}