#ifndef ENGIE_MOUSEINPUT_H
#define ENGIE_MOUSEINPUT_H

#include "windows.h"
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

class MouseInput
{
public:
	//Constructor for a MouseInput object
	MouseInput(int mouseSensitivity);
	//Destructor for a MouseInput object
	~MouseInput();
	//Initializes the mouseinput
	bool InitMouseInput(HWND hWnd);
	//Release the device
	void SaveReleaseDevice();
	//Acquire the device
	bool DoAcquire();
	//Get the mouse input
	void GetMouseInput();
	//Set the mouse data
	void SetTheMouseData();
	//Get relative x
	float GetRelativeX();
	//Get relative y
	float GetRelativeY();
private:
	DIPROPDWORD dipdw;
	LPDIRECTINPUT8 dInput;		
	LPDIRECTINPUTDEVICE8 dDevice;	
	DIMOUSESTATE mouseState;
	int mouseSensitivity;
};

#endif