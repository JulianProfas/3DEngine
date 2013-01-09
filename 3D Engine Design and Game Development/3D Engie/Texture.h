#ifndef ENGIE_TEXTURE_H
#define ENGIE_TEXTURE_H

#include <string>
#include <d3dx9.h>
#include "Logger.h"

class Texture
{
public:
	Texture(LPDIRECT3DDEVICE9 g_pd3dDevice, std::string pathName);
	~Texture();
	std::string GetName();
	LPDIRECT3DTEXTURE9* getTexture();
	void setTexture(void* texture);
	
private:
	LPDIRECT3DTEXTURE9* loadedTexture;
	std::string name;
	void loadTexture(LPDIRECT3DDEVICE9 g_pd3dDevice, std::string filePath);
};

#endif