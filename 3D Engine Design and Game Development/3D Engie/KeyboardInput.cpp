#define DIRECTINPUT_VERSION 0x0800
#include "KeyboardInput.h"

#define KEYDOWN(name, key) (name[key] & 0x80) 

/*
	Constructor for a KeyBoardInput object
*/
KeyboardInput::KeyboardInput()
{
	this->dInput = NULL;			
	this->dDevice = NULL;
}

/*
	Destructor for a KeyBoardInput object
*/
KeyboardInput::~KeyboardInput()
{

}

/*
	Initializes the keyboardinput, creating the devices
	@param hWnd, HWND needed for setting the cooperatelevel
*/
bool KeyboardInput::InitKeyboardInput(HWND hWnd)
{
	//DirectInput8Create should be done only once in manager
	HRESULT hr = DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&dInput, NULL);
	if FAILED(hr) 
	{
		return false; 
	}

	hr = dInput->CreateDevice(GUID_SysKeyboard, &dDevice, NULL);
	if FAILED(hr) 
	{ 
		SaveReleaseDevice(); 
		return false; 
	}

	hr = dDevice->SetDataFormat(&c_dfDIKeyboard); 
	if FAILED(hr) 
	{ 
		SaveReleaseDevice(); 
		return false; 
	} 

	hr = dDevice->SetCooperativeLevel(hWnd, DISCL_EXCLUSIVE | DISCL_FOREGROUND);
	if FAILED(hr)
	{ 
		SaveReleaseDevice(); 
		return false; 
	} 

	return true; 
}

/*
	Releases the devices
*/
void KeyboardInput::SaveReleaseDevice() 
{ 
	if (dInput) 
	{ 
		if (dDevice) 
		{ 
			dDevice->Unacquire(); 
			dDevice->Release();
			dDevice = NULL; 
		} 
		dInput->Release();
		dInput = NULL; 
	} 
} 


/*
	Checks if an key is pressed
	@param argKeyIsPressed, The key that needs to be checked if pressed
	@return bool, true if key is pressed, false otherwise
*/
bool KeyboardInput::ProcessKBInput(byte argKeyIsPressed) 
{ 
	if(!SUCCEEDED( dDevice->Poll() ))
	{
		this->DoAcquire();
	}
	
	byte keyBuffer[256]; 

	this->dDevice->GetDeviceState( sizeof(keyBuffer) , (LPVOID)&keyBuffer);
	
	// Check if keybuffer contains given key
	int pressed = KEYDOWN(keyBuffer, argKeyIsPressed);

	// pressed == 0 or 128 (0x80); meaning false or true
	if(pressed == 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

/*
	Acquire the device
*/
bool KeyboardInput::DoAcquire()
{
	if(SUCCEEDED(this->dDevice->Acquire()))
	{
		return true;
	}
	return false;
}

