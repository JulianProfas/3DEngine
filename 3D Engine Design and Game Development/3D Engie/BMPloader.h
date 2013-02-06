#ifndef BMPLOADER_H
#define BMPLOADER_H

#include <string>
#include <Windows.h>
#include "Logger.h"

class BMPloader
{
public:
	//Constructor for a BMPLoader 
	BMPloader();
	//Destructor for a BMPLoader
	~BMPloader();
	//Loads the heightdata from the file
	void LoadHeightMap(std::string fileName);
	//Get the heightdata
	unsigned char* GetHeightData();
	//Get the height of the heightmap
	int GetHeight();
	//Get the width of the heightmap
	int GetWidth();

private:
	//The heightdata of the heightmap
	unsigned char* heightData;
	//The height of the heightmap
	int height;
	//The width of the heightmap
	int width;
};

#endif