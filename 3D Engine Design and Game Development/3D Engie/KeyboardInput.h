#include "windows.h"
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include "Scene.h"

class KeyboardInput
{
public:
	KeyboardInput();
	KeyboardInput(HWND argHwnd);
	~KeyboardInput();
	bool InitKeyboardInput();
	void SaveReleaseDevice();
	bool ProcessKBInput(byte argKeyIsPressed);
	bool DoAcquire();
	void CheckKeyPressed(Scene* s);
private:
	LPDIRECTINPUT8 dInput;		
	LPDIRECTINPUTDEVICE8 dDevice;	
	HWND hwnd;
};

