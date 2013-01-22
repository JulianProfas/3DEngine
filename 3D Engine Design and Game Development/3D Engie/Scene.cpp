#include "Scene.h"

Scene::Scene(Renderer* r, ResourcesManager* rm, std::string sceneName)
{
	this->sceneRenderer  = r;
	this->resourceManager = rm;
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

			if(line.compare("Camera") == 0) // 0 means that the two strings match
			{
				//maak camera aan
			}
			else if(line.compare("Sky") == 0)
			{
				//maak sky aan
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
	this->sceneRenderer->SetupViewMatrix();

	// render sky

	// render terrain
	this->sceneTerrain->RenderTerrain(this->sceneRenderer);

	// render entitys
	for(EntityList::iterator i = this->sceneEntitys->begin(); i != this->sceneEntitys->end(); ++i)
	{
		i->renderEntityModel(this->sceneRenderer);
	}

	this->sceneRenderer->EndScene();
	this->sceneRenderer->PresentScene(hWnd);

}