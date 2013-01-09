#include "Texture.h"


Texture::Texture(LPDIRECT3DDEVICE9 g_pd3dDevice, std::string pathName)
{
	name = pathName;
	loadedTexture = new LPDIRECT3DTEXTURE9;
	//loadedTexture = NULL;
	loadTexture(g_pd3dDevice, pathName);
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


void Texture::loadTexture(LPDIRECT3DDEVICE9 g_pd3dDevice, std::string filePath)
{
	LPCSTR path = filePath.c_str();

	if(FAILED( D3DXCreateTextureFromFileA( 
	   g_pd3dDevice,
       path,
       loadedTexture)))
	{
		// Failed loading texture
		Logger::GetInstance()->Write("Failed loading texture");
	}
}
