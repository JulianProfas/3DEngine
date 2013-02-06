#ifndef ENGIE_KEYBOARDINPUT_H
#define ENGIE_KEYBOARDINPUT_H

#include "windows.h"
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

class KeyboardInput
{
public:
	//Constructor for a KeyBoardInput object
	KeyboardInput();
	//Destructor for a KeyBoardInput object
	~KeyboardInput();
	//Initializes the keyboardinput, creating the devices
	bool InitKeyboardInput(HWND argHwnd);
	//Releases the devices
	void SaveReleaseDevice();
	//Checks if an key is pressed
	bool ProcessKBInput(byte argKeyIsPressed);
	//Acquire the device
	bool DoAcquire();
private:
	LPDIRECTINPUT8 dInput;		
	LPDIRECTINPUTDEVICE8 dDevice;	
};

#endif
