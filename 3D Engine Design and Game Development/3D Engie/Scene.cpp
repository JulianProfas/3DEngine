#include "Scene.h"

/*
	Constructor for a Scene object
	@param scenePath, the URL to the scenefile
*/
Scene::Scene(std::string scenePath)
{
	this->scenePath = scenePath;
	this->entityList = new std::list<EntityModel>();
}

/*
	Destructor for a Scene object
*/
Scene::~Scene()
{
	this->ClearEntityList();
}

void Scene::LoadScene(Renderer* renderer, std::string sceneName)
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
				this->camera = new EntityCamera(posX, posY, posZ);
			}
			/*
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
			*/
			else if(line.compare("Terrain:") == 0)
			{
				std::string heightMap;
				std::string terrainTexture;

				fileStream >> heightMap >> terrainTexture;

				this->terrain = new Terrain(heightMap, terrainTexture);
			}
			else if(line.compare("Entity:") == 0)
			{
				float posX, posY, posZ, rotX, rotY, rotZ, scaX, scaY, scaZ;
				std::string modelPath;
				std::string texturePath;

				fileStream >> posX >> posY >> posZ >> rotX >> rotY >> rotZ >> scaX >> scaY >> scaZ >> modelPath >> texturePath;
				
				EntityModel* e = new EntityModel(posX, posY, posZ, rotX, rotY, rotZ, scaX, scaY, scaZ, modelPath, texturePath);
				this->entityList->push_back(*e);
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

*/
void Scene::PrepareScene(Renderer* renderer, ResourcesManager* resourceManager)
{
	Logger::GetInstance()->Write("Preparing scene: " + this->scenePath);

	//prepare terrain
	this->terrain->LoadResources(renderer, resourceManager);

	//prepare sky


	//prepare entitys
	for(std::list<EntityModel>::iterator i = this->entityList->begin(); i != this->entityList->end(); ++i)
	{
		i->LoadResources(resourceManager, renderer);
	}
}


/*
	Renders the scene to the window
*/
void Scene::RenderScene(Renderer* renderer, HWND hWnd)
{
	renderer->ClearScene();
	renderer->BeginScene();
	renderer->SetupProjectionMatrix();
	//this->sceneRenderer->SetupViewMatrix();
	//this->sceneCamera->CalculateViewMatrix(this->sceneRenderer);

	// render sky
	//renderer->Zenable(false);
	//this->sky->Render(renderer, camera);

	// render terrain
	renderer->Zenable(true);
	this->terrain->RenderTerrain(renderer);

	// render entitys
	for(std::list<EntityModel>::iterator i = this->entityList->begin(); i != this->entityList->end(); ++i)
	{
		i->renderEntityModel(renderer);
	}

	renderer->EndScene();
	renderer->PresentScene(hWnd);

}


void Scene::ClearEntityList()
{

}