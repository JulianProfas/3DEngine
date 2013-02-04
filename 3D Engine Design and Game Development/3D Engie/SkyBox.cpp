#include "SkyBox.h"

/*
	Constructor SkyBox.
*/
SkyBox::SkyBox(Renderer *renderer, std::vector<Texture*> textures)
{

	this->FillVertices(renderer);
	this->textures = textures;
}

/*
	Destructor SkyBox
*/
SkyBox::~SkyBox()
{

}

/*
	Renders the SkyBox
*/
void SkyBox::Render(Renderer* renderer, EntityCamera* camera)
{
	renderer->SetupWorldMatrix(camera->GetPositionX(), camera->GetPositionY(), camera->GetPositionZ(), 0, 0, 0, 1, 1, 1);
	renderer->SetStreamSource(this->vertexBufferIndex, sizeof(ENGIE_VERTEX));
	renderer->SetFvF(D3DFVF_CUSTOMVERTEX);
	
	int it = 5;
	for(int i = 0; i < 6; i++)
	{	
		LPDIRECT3DTEXTURE9 tex = *textures.at(it)->getTexture();
		renderer->SetTexture(tex);	
		renderer->DrawPrimitive(D3DPT_TRIANGLELIST, i * 6, 2);
		--it;
	}
	
}

/*
	Creates the vertices for the SkyBox
*/
void SkyBox::FillVertices(Renderer* renderer)
{
	// 36 vertices = 6 faces (cube) * 6 vertices per face
	//
	//0,0 ---- 1,0
	//   | \  |
	//   |  \ |
	//0,1------1,1

	this->numberOfVertices = 36;

	ENGIE_VERTEX vertices[36] =
	{
		// Front quad
		{-10.0f, -10.0f,  10.0f,  0.0f, 1.0f },
		{-10.0f,  10.0f,  10.0f,  0.0f, 0.0f },
		{ 10.0f, -10.0f,  10.0f,  1.0f, 1.0f },

		{ 10.0f, -10.0f,  10.0f,  1.0f, 1.0f },
		{-10.0f,  10.0f,  10.0f,  0.0f, 0.0f },
		{ 10.0f,  10.0f,  10.0f,  1.0f, 0.0f },
	
	
		// Back quad
		{-10.0f, -10.0f,  -10.0f,  1.0f, 1.0f },
		{ 10.0f, -10.0f,  -10.0f,  0.0f, 1.0f },
		{-10.0f,  10.0f,  -10.0f,  1.0f, 0.0f },
	
		{ 10.0f, -10.0f,  -10.0f,  0.0f, 1.0f },
		{ 10.0f,  10.0f,  -10.0f,  0.0f, 0.0f },
		{-10.0f,  10.0f,  -10.0f,  1.0f, 0.0f },

		// Left quad
		{-10.0f, -10.0f, -10.0f,  0.0f, 1.0f },
		{-10.0f,  10.0f, -10.0f,  0.0f, 0.0f },
		{-10.0f,  10.0f,  10.0f,  1.0f, 0.0f },

		{-10.0f,  10.0f,  10.0f,  1.0f, 0.0f },
		{-10.0f, -10.0f,  10.0f,  1.0f, 1.0f },
		{-10.0f, -10.0f, -10.0f,  0.0f, 1.0f },
	
		// Right quad
		{10.0f,  10.0f, -10.0f,  1.0f, 0.0f }, 
		{10.0f, -10.0f, -10.0f,  1.0f, 1.0f }, 
		{10.0f, -10.0f,  10.0f,  0.0f, 1.0f }, 

		{10.0f, -10.0f,  10.0f,  0.0f, 1.0f }, 
		{10.0f, 10.0f,  10.0f,   0.0f, 0.0f },
		{10.0f, 10.0f,  -10.0f,  1.0f, 0.0f }, 


		// Top quad
		{-10.0f,  10.0f,  10.0f,  0.0f, 1.0f },
		{-10.0f,  10.0f, -10.0f,  0.0f, 0.0f },
		{ 10.0f,  10.0f, -10.0f,  1.0f, 0.0f },

		{-10.0f,  10.0f,  10.0f,  0.0f, 1.0f },
		{ 10.0f,  10.0f, -10.0f,  1.0f, 0.0f },
		{ 10.0f,  10.0f,  10.0f,  1.0f, 1.0f },

	
		// Bottom quad
		{-10.0f,  -10.0f,  10.0f,  0.0f, 0.0f },
		{ 10.0f,  -10.0f, -10.0f,  1.0f, 1.0f },
		{-10.0f,  -10.0f, -10.0f,  0.0f, 1.0f },
	
		{-10.0f,  -10.0f,  10.0f,  0.0f, 0.0f },
		{ 10.0f,  -10.0f,  10.0f,  1.0f, 0.0f },
		{ 10.0f,  -10.0f, -10.0f,  1.0f, 1.0f },
	};

	Logger::GetInstance()->Write("Created SkyBox vertices");
	this->vertexBufferIndex = renderer->CreateVertexBuffer(vertices, 36);  
	Logger::GetInstance()->Write("Created SkyBox vertexbuffer");
}