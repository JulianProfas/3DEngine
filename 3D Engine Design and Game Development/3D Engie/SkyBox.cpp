#include "SkyBox.h"

/*
	Constructor for a SkyBox object
	@param texturePath, 6 URLs to a texture file
*/
SkyBox::SkyBox(std::string texturePath [6])
{
	for(int i = 0; i < 6; ++i)
	{
		this->texturePath[i] = texturePath[i];
	}
	
	Logger::GetInstance()->Write("Succesfully created SkyBox");
}

/*
	Destructor for a SkyBox object
*/
SkyBox::~SkyBox()
{

}

/*
	Renders the SkyBox
	@param renderer, Renderer object needed for rendering the skybox
	@param camera, EntityCamera object for setting the worldmatrix
*/
void SkyBox::Render(Renderer* renderer, EntityCamera* camera)
{

	float x = -camera->GetPositionX();
	float y = -camera->GetPositionY();
	float z = -camera->GetPositionZ();

	renderer->SetupWorldMatrix(x, y, z, 0, 0, 0, 1, 1, 1, camera);
	renderer->SetStreamSource(this->vertexBufferIndex, sizeof(ENGIE_VERTEX));
	renderer->SetFvF(D3DFVF_CUSTOMVERTEX);
	
	for(int i = 0; i < 6; i++)
	{	
		renderer->SetTexture(this->texture[i]);	
		renderer->DrawPrimitiveTriangle(i * 6, 2);
	}
	
	
}

/*
	Creates the vertices and vertex buffer which resembles the SkyBox
	@param renderer, Renderer object for creating the vertex buffer
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

/*
	Loads all resources need for a Skybox object, including creating the vertices and vertex buffer
	@param renderer, Renderer object for loading textures
	@param resourceManager, ResourcesManager object to manage the loaded textures
*/
void SkyBox::LoadResources(Renderer* renderer, ResourcesManager* resourceManager)
{
	this->FillVertices(renderer);

	for(int i = 0; i < 6; ++i)
	{
		this->texture[i] = resourceManager->LoadTexture(renderer->GetDevice(), this->texturePath[i]);
	}
}