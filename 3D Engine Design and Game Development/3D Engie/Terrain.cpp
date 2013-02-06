#include "Terrain.h"

/*
	The constuctor for a Terrain object
	@param terrainPath, The URL to the heightmap file
	@param texturePath, The URL to the texture file
	@param posX, The x position for the terrain
	@param posY, The y position for the terrain
	@param posZ, The z position for the terrain
	@param scale, The scaling for the height data
*/
Terrain::Terrain(std::string terrainPath, std::string texturePath, float posX, float posY, float posZ, int scale)
{
	this->positionX = posX;
	this->positionY = posY;
	this->positionZ = posZ;
	this->terrainPath = terrainPath;
	this->texturePath = texturePath;
	this->scale = scale;

	Logger::GetInstance()->Write("Succesfully created terrain");
}

/*
	Destructor for a Terrain object
*/
Terrain::~Terrain()
{

}

/*
	Load all resources needed for rendering a terrain, this includes the creation of the vertices
	@param renderer, Renderer object for loading texture and creating a vertex buffer
	@param resourceManager, ResourcesManager object for managing the texture
*/
void Terrain::LoadResources(Renderer* renderer, ResourcesManager* resourceManager)
{
	Logger::GetInstance()->Write("Loading terrain resources...");

	//create BMPloader object 
	m_BMPLoader = new BMPloader();
	m_BMPLoader->LoadHeightMap(this->terrainPath);

	texture = resourceManager->LoadTexture(renderer->GetDevice(), this->texturePath);

	FillVertices(renderer);

	Logger::GetInstance()->Write("Terrain resources loaded");
}

/*
	Get the index for the vertex buffer map
*/
int Terrain::GetVertexBufferIndex()
{
	return this->vertexBufferIndex;
}

/*
	Get the texture
*/
Texture* Terrain::GetTexture()
{
	return this->texture;
}

/* 
	Creates the vertices for the terrain and creates a vertex buffer for the vertices
	@param renderer, Renderer object for creating the vertex buffer
*/
void Terrain::FillVertices(Renderer* renderer)
{
	//each square has two triangles and thus 6 vertices (not indexed)
	terrainVertices = new ENGIE_VERTEX[m_BMPLoader->GetWidth() * m_BMPLoader->GetHeight() * 6];
	this->numberOfVertices = 0;

	//divide all height values by scale, because it is mapped from 0 to 255 in the heightmap
	//get the width and height minus 1 because else we cross the bounds of the array with the (x + 1) and (y + 1) lookups
	for (int x = 0; x < this->m_BMPLoader->GetWidth()-1; x++)
	{
		for (int y = 0; y < this->m_BMPLoader->GetHeight()-1; y++)
		{
			//0,0 ---- 1,0
			//   | \  |
			//   |  \ |
			//0,1------1,1

			//0,0
			this->terrainVertices[numberOfVertices].x = (float)x;
			this->terrainVertices[numberOfVertices].y = (float)this->m_BMPLoader->GetHeightData()[(y*this->m_BMPLoader->GetWidth())+x]/this->scale;
			this->terrainVertices[numberOfVertices].z = (float)y;
			this->terrainVertices[numberOfVertices].tu = ((float)x/(this->m_BMPLoader->GetWidth()-1)*1.0f);
			this->terrainVertices[numberOfVertices].tv = ((float)y/(this->m_BMPLoader->GetHeight()-1)*1.0f);
				  
			//0,1 
			this->terrainVertices[numberOfVertices+1].x = (float)x;
			this->terrainVertices[numberOfVertices+1].y = (float)this->m_BMPLoader->GetHeightData()[((y+1)*this->m_BMPLoader->GetWidth())+x]/this->scale;
			this->terrainVertices[numberOfVertices+1].z = (float)y+1;
			this->terrainVertices[numberOfVertices+1].tu = ((float)x/(this->m_BMPLoader->GetWidth()-1)*1.0f);
			this->terrainVertices[numberOfVertices+1].tv = ((float)(y+1)/(this->m_BMPLoader->GetHeight()-1)*1.0f);
				  
			//1,1 
			this->terrainVertices[numberOfVertices+2].x = (float)x+1;
			this->terrainVertices[numberOfVertices+2].y = (float)this->m_BMPLoader->GetHeightData()[((y+1)*this->m_BMPLoader->GetWidth())+x+1]/this->scale;
			this->terrainVertices[numberOfVertices+2].z = (float)y+1;
			this->terrainVertices[numberOfVertices+2].tu = ((float)(x+1)/(this->m_BMPLoader->GetWidth()-1)*1.0f);
			this->terrainVertices[numberOfVertices+2].tv = ((float)(y+1)/(this->m_BMPLoader->GetHeight()-1)*1.0f);
				  
			//0,0 
			this->terrainVertices[numberOfVertices+3].x = (float)x;
			this->terrainVertices[numberOfVertices+3].y = (float)this->m_BMPLoader->GetHeightData()[(y*this->m_BMPLoader->GetWidth())+x]/this->scale;
			this->terrainVertices[numberOfVertices+3].z = (float)y;
			this->terrainVertices[numberOfVertices+3].tu = ((float)x/(this->m_BMPLoader->GetWidth()-1)*1.0f);
			this->terrainVertices[numberOfVertices+3].tv = ((float)y/(this->m_BMPLoader->GetHeight()-1)*1.0f);
				  
			//1,1 
			this->terrainVertices[numberOfVertices+4].x = (float)x+1;
			this->terrainVertices[numberOfVertices+4].y = (float)this->m_BMPLoader->GetHeightData()[((y+1)*this->m_BMPLoader->GetWidth())+x+1]/this->scale;
			this->terrainVertices[numberOfVertices+4].z = (float)y+1;
			this->terrainVertices[numberOfVertices+4].tu = ((float)(x+1)/(this->m_BMPLoader->GetWidth()-1)*1.0f);
			this->terrainVertices[numberOfVertices+4].tv = ((float)(y+1)/(this->m_BMPLoader->GetHeight()-1)*1.0f);
				 
			//1, 0
			this->terrainVertices[numberOfVertices+5].x = (float)x+1;
			this->terrainVertices[numberOfVertices+5].y = (float)this->m_BMPLoader->GetHeightData()[(y*this->m_BMPLoader->GetWidth())+x+1]/this->scale;
			this->terrainVertices[numberOfVertices+5].z = (float)y;
			this->terrainVertices[numberOfVertices+5].tu = ((float)(x+1)/(this->m_BMPLoader->GetWidth()-1)*1.0f);;
			this->terrainVertices[numberOfVertices+5].tv = ((float)y/(this->m_BMPLoader->GetHeight()-1)*1.0f);;

			this->numberOfVertices += 6;
		}
	}	
	Logger::GetInstance()->Write("Created terrain vertices");

	this->vertexBufferIndex = renderer->CreateVertexBuffer(this->terrainVertices, this->numberOfVertices);
	
	Logger::GetInstance()->Write("Created terrain vertexbuffer");
}

/*
	Terrain renders its vertices, with texture
	@param, Renderer object needed to render the terrain
	@param, EntityCamera object for setting the world matrix
*/
void Terrain::RenderTerrain(Renderer* renderer, EntityCamera* camera)
{
	renderer->SetupWorldMatrix(this->positionX, this->positionY, this->positionZ, 0, 0, 0, 1, 1, 1, camera);
	renderer->SetStreamSource(this->vertexBufferIndex, sizeof(ENGIE_VERTEX));
	renderer->SetFvF(D3DFVF_CUSTOMVERTEX);
	renderer->SetTexture(this->texture);
	renderer->DrawPrimitiveTriangle(0, this->numberOfVertices/3);
}