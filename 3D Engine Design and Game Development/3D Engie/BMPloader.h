#ifndef BMPLOADER_H
#define BMPLOADER_H

#include <string>
#include <Windows.h>
#include "Logger.h"

class BMPloader
{
public:
	BMPloader();
	~BMPloader();
	void LoadHeightMap(std::string fileName);
	unsigned char* GetHeightData();
	int GetHeight();
	int GetWidth();
private:
	unsigned char* heightData;
	int height;
	int width;
};

#endif