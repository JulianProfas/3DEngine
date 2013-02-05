#ifndef ENGIE_TEXTURE_H
#define ENGIE_TEXTURE_H

#include <string>
#include <d3dx9.h>
#include "Logger.h"

class Texture
{
public:
	//Constructor for a Texture object
	Texture(void* device, std::string filePath);
	//Destructor for a Texture object
	~Texture();
	//Get the directx 9 Texture
	LPDIRECT3DTEXTURE9* getTexture();

private:
	//Load the directx 9 Texture from given filePath
	void loadTexture(void* device, std::string filePath);

	//Directx 9 Texture
	LPDIRECT3DTEXTURE9* loadedTexture;
};

#endif