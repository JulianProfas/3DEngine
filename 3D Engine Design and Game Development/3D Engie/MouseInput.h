#ifndef MOUSEINPUT_H
#define MOUSEINPUT_H

#include "windows.h"
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

class MouseInput
{
public:
	MouseInput();
	MouseInput(HWND argHwnd);
	~MouseInput();
	bool InitMouseInput();
	void SaveReleaseDevice();
	bool DoAcquire();
	void CheckKeyPressed();
	void ResetMouseStruct();
	bool GetMouseInput();
	void SetTheMouseBuffer();
private:
	DIPROPDWORD dipdw;
	LPDIRECTINPUT8 dInput;		
	LPDIRECTINPUTDEVICE8 dDevice;	
	HWND hwnd;
	struct BufferedMouse;
};

#endif