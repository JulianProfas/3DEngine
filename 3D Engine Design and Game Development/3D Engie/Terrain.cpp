#include "Terrain.h"

Terrain::Terrain(std::string terrainFileName, std::string texturefilename, Renderer* renderer, ResourcesManager* resourceManager)
{
	m_BMPLoader = new BMPloader();
	m_BMPLoader->LoadHeightMap(terrainFileName);

	texture = &resourceManager->LoadTexture(texturefilename);

	FillVertices(renderer);
}

Terrain::~Terrain()
{

}

LPDIRECT3DVERTEXBUFFER9 Terrain::GetVertexBuffer()
{
	return VB;
}

int Terrain::GetNumberOfVertices()
{
	return this->numberOfVertices;
}

Texture* Terrain::GetTexture()
{
	return this->texture;
}


void Terrain::FillVertices(Renderer* renderer)
{
	//each square has two triangles and thus 6 vertices (not indexed)
	vertices = new ENGIE_VERTEX[m_BMPLoader->GetWidth() * m_BMPLoader->GetHeight() * 6];
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
			this->vertices[numberOfVertices].x = (float)x;
			this->vertices[numberOfVertices].y = (float)this->m_BMPLoader->GetHeightData()[(y*this->m_BMPLoader->GetWidth())+x]/scale;
			this->vertices[numberOfVertices].z = (float)y;
			this->vertices[numberOfVertices].tu = ((float)x/(this->m_BMPLoader->GetWidth()-1)*1.0f);
			this->vertices[numberOfVertices].tv = ((float)y/(this->m_BMPLoader->GetHeight()-1)*1.0f);
			
			//0,1
			this->vertices[numberOfVertices+1].x = (float)x;
			this->vertices[numberOfVertices+1].y = (float)this->m_BMPLoader->GetHeightData()[((y+1)*this->m_BMPLoader->GetWidth())+x]/scale;
			this->vertices[numberOfVertices+1].z = (float)y+1;
			this->vertices[numberOfVertices+1].tu = ((float)x/(this->m_BMPLoader->GetWidth()-1)*1.0f);
			this->vertices[numberOfVertices+1].tv = ((float)(y+1)/(this->m_BMPLoader->GetHeight()-1)*1.0f);
			
			//1,1
			this->vertices[numberOfVertices+2].x = (float)x+1;
			this->vertices[numberOfVertices+2].y = (float)this->m_BMPLoader->GetHeightData()[((y+1)*this->m_BMPLoader->GetWidth())+x+1]/scale;
			this->vertices[numberOfVertices+2].z = (float)y+1;
			this->vertices[numberOfVertices+2].tu = ((float)(x+1)/(this->m_BMPLoader->GetWidth()-1)*1.0f);
			this->vertices[numberOfVertices+2].tv = ((float)(y+1)/(this->m_BMPLoader->GetHeight()-1)*1.0f);

			//0,0
			this->vertices[numberOfVertices+3].x = (float)x;
			this->vertices[numberOfVertices+3].y = (float)this->m_BMPLoader->GetHeightData()[(y*this->m_BMPLoader->GetWidth())+x]/scale;
			this->vertices[numberOfVertices+3].z = (float)y;
			this->vertices[numberOfVertices+3].tu = ((float)x/(this->m_BMPLoader->GetWidth()-1)*1.0f);
			this->vertices[numberOfVertices+3].tv = ((float)y/(this->m_BMPLoader->GetHeight()-1)*1.0f);
			
			//1,1
			this->vertices[numberOfVertices+4].x = (float)x+1;
			this->vertices[numberOfVertices+4].y = (float)this->m_BMPLoader->GetHeightData()[((y+1)*this->m_BMPLoader->GetWidth())+x+1]/scale;
			this->vertices[numberOfVertices+4].z = (float)y+1;
			this->vertices[numberOfVertices+4].tu = ((float)(x+1)/(this->m_BMPLoader->GetWidth()-1)*1.0f);
			this->vertices[numberOfVertices+4].tv = ((float)(y+1)/(this->m_BMPLoader->GetHeight()-1)*1.0f);
			
			//1, 0
			this->vertices[numberOfVertices+5].x = (float)x+1;
			this->vertices[numberOfVertices+5].y = (float)this->m_BMPLoader->GetHeightData()[(y*this->m_BMPLoader->GetWidth())+x+1]/scale;
			this->vertices[numberOfVertices+5].z = (float)y;
			this->vertices[numberOfVertices+5].tu = ((float)(x+1)/(this->m_BMPLoader->GetWidth()-1)*1.0f);;
			this->vertices[numberOfVertices+5].tv = ((float)y/(this->m_BMPLoader->GetHeight()-1)*1.0f);;

			this->numberOfVertices += 6;
		}
	}	
	Logger::GetInstance()->Write("Created terrain vertices");

	VB = renderer->CreateVertexBuffer(this->vertices, this->numberOfVertices);
	
	Logger::GetInstance()->Write("Created terrain vertexbuffer");
}