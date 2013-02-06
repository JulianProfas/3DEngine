#include "Scene.h"

/*
	Constructor for a Scene object
	@param scenePath, the URL to the scenefile
*/
Scene::Scene(std::string scenePath)
{
	this->scenePath = scenePath;
	this->entityList = new std::list<EntityModel>();
	this->sceneLoaded = false;
	this->scenePrepared = false;
}

/*
	Destructor for a Scene object
*/
Scene::~Scene()
{
	this->ClearEntityList();
}

/*
	Loads a Scene from a textfile
	@param filePath, The URL to the text file
*/
void Scene::LoadScene(std::string scenePath)
{
	Logger::GetInstance()->Write("Loading scene: " + this->scenePath);
	
	std::ifstream fileStream(scenePath);

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
			else if(line.compare("SkyBox:") == 0)
			{
				std::string textures [6];
				fileStream >> textures[0] >> textures[1] >> textures[2] >> textures[3] >> textures[4] >>textures[5];
				
				this->sky = new SkyBox(textures);
			}
			else if(line.compare("Terrain:") == 0)
			{
				std::string heightMap;
				std::string terrainTexture;
				float posX, posY, posZ;
				int scale;

				fileStream >> posX >> posY >> posZ >> heightMap >> terrainTexture >> scale;

				this->terrain = new Terrain(heightMap, terrainTexture, posX, posY, posZ, scale);
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
		
		if(NULL == this->sky)
		{
			Logger::GetInstance()->Write("SkyBox not found in: " + this->scenePath);
		}
		if(NULL == this->terrain)
		{
			Logger::GetInstance()->Write("Terrain not found in: " + this->scenePath);
		}
		if(NULL == this->camera)
		{
			Logger::GetInstance()->Write("Camera not found in: " + this->scenePath);
			Logger::GetInstance()->Write("Creating default camera for: " + this->scenePath);
			this->camera = new EntityCamera(0, 0, 0);
		}

		Logger::GetInstance()->Write("Scene: " + this->scenePath + " loaded");

		this->sceneLoaded = true;
	}
	else
	{
		Logger::GetInstance()->Write("Can't open scene file: " + this->scenePath);
	}
}

/*
	Prepares the Scene by loading all resources for terrain, sky and entitys
	@param renderer, Renderer object for loading textures/models and creating vertex buffers
	@param resourceManager, ResourcesManager object for managing all textures and models
*/
void Scene::PrepareScene(Renderer* renderer, ResourcesManager* resourceManager)
{
	Logger::GetInstance()->Write("Preparing scene: " + this->scenePath);

	//prepare terrain
	if(NULL != this->terrain)
	{
		this->terrain->LoadResources(renderer, resourceManager);
	}
	
	//prepare sky
	if(NULL != this->terrain)
	{
		this->sky->LoadResources(renderer, resourceManager);
	}

	//prepare entitys
	for(std::list<EntityModel>::iterator i = this->entityList->begin(); i != this->entityList->end(); ++i)
	{
		i->LoadResources(resourceManager, renderer);
	}

	Logger::GetInstance()->Write("Scene: " + this->scenePath + " prepared");

	this->scenePrepared = true;
}


/*
	Renders the scene to the window
	@param renderer, Renderer object for rendering the objects
	@param hWnd, HWND object which specifies where the scene is rendered
*/
void Scene::RenderScene(Renderer* renderer, HWND hWnd)
{
	//check if scene is loaded
	if(this->sceneLoaded)
	{
		//check if scene is prepared
		if(this->scenePrepared)
		{
			renderer->ClearScene();
			renderer->BeginScene();
			renderer->SetupProjectionMatrix();
			//this->sceneRenderer->SetupViewMatrix();
	
			// render sky
			renderer->Zenable(false);
			this->sky->Render(renderer, camera);

			// render terrain
			renderer->Zenable(true);
			this->terrain->RenderTerrain(renderer, camera);

			// render entitys
			for(std::list<EntityModel>::iterator i = this->entityList->begin(); i != this->entityList->end(); ++i)
			{
				i->renderEntityModel(renderer, camera);
			}

			renderer->EndScene();
			renderer->PresentScene(hWnd);
		}
		else
		{
			Logger::GetInstance()->Write("Prepare scene: " + this->scenePath + " before rendering");
		}
		
	}
	else
	{
		Logger::GetInstance()->Write("Load scene: " + this->scenePath + " before rendering");
	}
}

/*
	Removes all EntityModel objects from the entityList
*/
void Scene::ClearEntityList()
{
	this->entityList->clear();
}

/*
	Get the camera
*/
EntityCamera* Scene::GetCamera()
{
	return this->camera;
}