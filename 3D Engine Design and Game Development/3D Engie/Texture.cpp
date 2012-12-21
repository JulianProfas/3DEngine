#include "Texture.h"


Texture::Texture(std::string& argName, LPDIRECT3DTEXTURE9 texture)
{
	name = argName;
	loadedTexture = texture;
}


Texture::~Texture()
{
	loadedTexture->Release();
}

std::string Texture::GetName()
{
	return name;
}

void* Texture::getTexture()
{
	return loadedTexture;
}

void Texture::setTexture(void* texture)
{
	loadedTexture = (LPDIRECT3DTEXTURE9)texture;
}

Texture* Texture::loadTexture()
{
