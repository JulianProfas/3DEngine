#include "Scene.h"

Scene::Scene()
{

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

			if(line.compare("Camera") != 0)
			{
				//maak camera aan
			}
			else if(line.compare("Sky") != 0)
			{
				//maak sky aan
			}
			else if(line.compare("Terrain") != 0)
			{
				//maak terrain aan
			}
			else if(line.compare("Entity") != 0)
			{
				//maak entity aan
			}
			std::cout << line << std::endl;
		}
		
	}
	else
	{
		Logger::GetInstance()->Write("can't open scene file: " + sceneName);
	}
}

void Scene::RenderScene()
{

}