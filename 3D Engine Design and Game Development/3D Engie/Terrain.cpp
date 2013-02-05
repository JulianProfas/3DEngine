#include "Terrain.h"

Terrain::Terrain(std::string terrainPath, std::string texturePath)
{
	this->posX = -128;
	this->posY = -10;
	this->posZ = -128;
	this->terrainPath = terrainPath;
	this->texturePath = texturePath;

	Logger::GetInstance()->Write("Succesfully created terrain");
}

Terrain::~Terrain()
{

}

void Terrain::LoadResources(Renderer* renderer, ResourcesManager* resourceManager)
{
	//create BMPloader object 
	m_BMPLoader = new BMPloader();
	m_BMPLoader->LoadHeightMap(this->terrainPath);

	texture = resourceManager->LoadTexture(renderer->GetDevice(), this->texturePath);

	FillVertices(renderer);

}

int Terrain::GetVertexBufferIndex()
{
	return this->vertexBufferIndex;
}

int Terrain::GetNumberOfVertices()
{
	return this->numberOfVertices;
}

Texture* Terrain::GetTexture()
{
	return this->texture;
}

/* 
	Creates the vertices for the terrain
*/
void Terrain::FillVertices(Renderer* renderer)
{
	//each square has two triangles and thus 6 vertices (not indexed)
	terrainVertices = new ENGIE_VERTEX[m_BMPLoader->GetWidth() * m_BMPLoader->GetHeight() * 6];
	this->numberOfVertices = 0;

	float scale = 10;

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
			this->terrainVertices[numberOfVertices].y = (float)this->m_BMPLoader->GetHeightData()[(y*this->m_BMPLoader->GetWidth())+x]/scale;
			this->terrainVertices[numberOfVertices].z = (float)y;
			this->terrainVertices[numberOfVertices].tu = ((float)x/(this->m_BMPLoader->GetWidth()-1)*1.0f);
			this->terrainVertices[numberOfVertices].tv = ((float)y/(this->m_BMPLoader->GetHeight()-1)*1.0f);
				  
			//0,1 
			this->terrainVertices[numberOfVertices+1].x = (float)x;
			this->terrainVertices[numberOfVertices+1].y = (float)this->m_BMPLoader->GetHeightData()[((y+1)*this->m_BMPLoader->GetWidth())+x]/scale;
			this->terrainVertices[numberOfVertices+1].z = (float)y+1;
			this->terrainVertices[numberOfVertices+1].tu = ((float)x/(this->m_BMPLoader->GetWidth()-1)*1.0f);
			this->terrainVertices[numberOfVertices+1].tv = ((float)(y+1)/(this->m_BMPLoader->GetHeight()-1)*1.0f);
				  
			//1,1 
			this->terrainVertices[numberOfVertices+2].x = (float)x+1;
			this->terrainVertices[numberOfVertices+2].y = (float)this->m_BMPLoader->GetHeightData()[((y+1)*this->m_BMPLoader->GetWidth())+x+1]/scale;
			this->terrainVertices[numberOfVertices+2].z = (float)y+1;
			this->terrainVertices[numberOfVertices+2].tu = ((float)(x+1)/(this->m_BMPLoader->GetWidth()-1)*1.0f);
			this->terrainVertices[numberOfVertices+2].tv = ((float)(y+1)/(this->m_BMPLoader->GetHeight()-1)*1.0f);
				  
			//0,0 
			this->terrainVertices[numberOfVertices+3].x = (float)x;
			this->terrainVertices[numberOfVertices+3].y = (float)this->m_BMPLoader->GetHeightData()[(y*this->m_BMPLoader->GetWidth())+x]/scale;
			this->terrainVertices[numberOfVertices+3].z = (float)y;
			this->terrainVertices[numberOfVertices+3].tu = ((float)x/(this->m_BMPLoader->GetWidth()-1)*1.0f);
			this->terrainVertices[numberOfVertices+3].tv = ((float)y/(this->m_BMPLoader->GetHeight()-1)*1.0f);
				  
			//1,1 
			this->terrainVertices[numberOfVertices+4].x = (float)x+1;
			this->terrainVertices[numberOfVertices+4].y = (float)this->m_BMPLoader->GetHeightData()[((y+1)*this->m_BMPLoader->GetWidth())+x+1]/scale;
			this->terrainVertices[numberOfVertices+4].z = (float)y+1;
			this->terrainVertices[numberOfVertices+4].tu = ((float)(x+1)/(this->m_BMPLoader->GetWidth()-1)*1.0f);
			this->terrainVertices[numberOfVertices+4].tv = ((float)(y+1)/(this->m_BMPLoader->GetHeight()-1)*1.0f);
				 
			//1, 0
			this->terrainVertices[numberOfVertices+5].x = (float)x+1;
			this->terrainVertices[numberOfVertices+5].y = (float)this->m_BMPLoader->GetHeightData()[(y*this->m_BMPLoader->GetWidth())+x+1]/scale;
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
*/
void Terrain::RenderTerrain(Renderer* renderer)
{
	renderer->SetupWorldMatrix(posX, posY, posZ, 0, 0, 0, 1, 1, 1);
	renderer->SetStreamSource(this->vertexBufferIndex, sizeof(ENGIE_VERTEX));
	renderer->SetFvF(D3DFVF_CUSTOMVERTEX);
	renderer->SetTexture(this->texture);
	renderer->DrawPrimitiveTriangle(0, this->numberOfVertices/3);
}

void Terrain::SetPositionX(float x)
{
	this->posX = x;
}

void Terrain::SetPositionY(float y)
{
	this->posY = y;
}

void Terrain::SetPositionZ(float z)
{
	this->posZ = z;
}

