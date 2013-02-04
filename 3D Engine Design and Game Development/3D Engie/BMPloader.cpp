#include "BMPloader.h"

BMPloader::BMPloader()
{

}

BMPloader::~BMPloader()
{

}

void BMPloader::LoadHeightMap(std::string fileName)
{
	//Load image from file
	HDC lhdcDest = NULL;	//Handle to Device Context (Windows GDI)
	HANDLE hbmp = NULL;	//Handle to an object (standard handle)
	HINSTANCE hInst = NULL;//Handle to an instance (instance of the window)

	//Create a memory device context compatible with the specified device (NULL)
	lhdcDest = CreateCompatibleDC(NULL);
	if (lhdcDest == NULL)	 
	{		  
		DeleteDC(lhdcDest);	//Delete the DC (prevents a memory leak!
	}

	//Windows GDI load image of type BMP (fileformat)
	hbmp = LoadImage(hInst, fileName.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	if (hbmp == NULL)	//Give a visual warning if the loading of the image failed
	{
		char s[100];
		wsprintf(s, "Can't find HeightMask3 %s", fileName);
		MessageBox(NULL, s, "ERROR ERROR ERROR", MB_OK);
	}
	
	SelectObject(lhdcDest, hbmp);

	//The BITMAP structure defines the type, width, height, color format, and bit values of a bitmap
	BITMAP bm;

	GetObject(hbmp, sizeof(BITMAP), (void*)&bm);

	//Store the width and height of the heightmap
	width = bm.bmWidth;
	height = bm.bmHeight;
	
	//Create an array to hold all the heightdata
	heightData = new unsigned char[width*height];

	//Iterate through the BMP-file and fill the heightdata-array
	
	for (int lHeight = 0; lHeight < height; lHeight++)
	{
		for (int lWidth = 0; lWidth < width; lWidth++)
		{
			heightData[(lHeight * width) + lWidth] = GetRValue(GetPixel(lhdcDest, lHeight, lWidth));	
		}
	}

	Logger::GetInstance()->Write("Height data loaded");

}

int BMPloader::GetHeight()
{
	return height;
}

int BMPloader::GetWidth()
{
	return width;
}

BYTE* BMPloader::GetHeightData()
{
	return heightData;
}