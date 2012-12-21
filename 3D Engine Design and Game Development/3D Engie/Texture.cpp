#include "Texture.h"


Texture::Texture(LPDIRECT3DDEVICE9 g_pd3dDevice, std::string argName)
{
	name = argName;
	loadedTexture = new LPDIRECT3DTEXTURE9;
	//loadedTexture = NULL;
	loadTexture(g_pd3dDevice);
}


Texture::~Texture()
{
	//loadedTexture->Release();
}

std::string Texture::GetName()
{
	return name;
}

LPDIRECT3DTEXTURE9* Texture::getTexture()
{
	return loadedTexture;
}


void Texture::loadTexture(LPDIRECT3DDEVICE9 g_pd3dDevice)
{
	if(FAILED( D3DXCreateTextureFromFileA( 
	   g_pd3dDevice,
       "tiger.bmp",
       loadedTexture)))
	{
		// Failed loading texture
		Logger::GetInstance()->Write("Failed loading texture");
	}
}
