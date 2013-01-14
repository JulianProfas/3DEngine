#ifndef BMPLOADER_H
#define BMPLOADER_H

#include <string>
#include <Windows.h>
#include "Logger.h"

typedef unsigned char BYTE;
class BMPloader
{
public:
	BMPloader();
	~BMPloader();
	void LoadHeightMap(std::string fileName);
	BYTE* GetHeightData();
	int GetHeight();
	int GetWidth();
private:
	BYTE* heightData;
	int height;
	int width;
};

#endif