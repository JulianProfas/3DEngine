#include "Texture.h"

/*
	Constructor for a Texture object
	@param device, a directx 9 device is needed for the loadTexture method
	@param filePath, the URL to the texturefile
*/
Texture::Texture(LPDIRECT3DDEVICE9 device, std::string filePath)
{
	loadedTexture = new LPDIRECT3DTEXTURE9;
	loadTexture(device, filePath);
}

/*
	Destructor for a Texture object
*/
Texture::~Texture()
{
	
}

/*
	Get the directx 9 texture
*/
LPDIRECT3DTEXTURE9* Texture::getTexture()
{
	return loadedTexture;
}

/*
	Load the directx 9 Texture from given filePath
	@param device, a directx 9 device 
	@param filePath, the URL to the texturefile
*/
void Texture::loadTexture(LPDIRECT3DDEVICE9 device, std::string filePath)
{
	LPCSTR path = filePath.c_str();

	if(FAILED( D3DXCreateTextureFromFileA( 
	   device,
       path,
       loadedTexture)))
	{
		// Failed loading texture
		Logger::GetInstance()->Write("Failed loading texture: " + filePath);
	}
	else
	{
		Logger::GetInstance()->Write("Succesfully loaded texture: " + filePath);
	}
}
