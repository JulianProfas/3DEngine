#ifndef MOUSEINPUT_H
#define MOUSEINPUT_H

#include "windows.h"
#include "Scene.h" 
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
	bool GetMouseInput(Scene* s);
	void SetTheMouseBuffer(Scene* s);
	float GetRelativeX();
	float GetRelativeY();
private:
	DIPROPDWORD dipdw;
	LPDIRECTINPUT8 dInput;		
	LPDIRECTINPUTDEVICE8 dDevice;	
	HWND hwnd;
	DIMOUSESTATE mouseState;
};

#endif