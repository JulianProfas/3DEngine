#define DIRECTINPUT_VERSION 0x0800

#include "MouseInput.h"
#include <iostream>

/*
	Constructor for a MouseInput object
	@param mouseSensitivity, the relative x and y are divide by this number
*/
MouseInput::MouseInput(int mouseSensitivity)
{
	this->mouseSensitivity = mouseSensitivity;
	const int MOUSEBUFFER = 8;

	dipdw.diph.dwSize			= sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize		= sizeof(DIPROPHEADER);
	dipdw.diph.dwObj			= 0;
	dipdw.diph.dwHow			= DIPH_DEVICE;
	dipdw.dwData				= MOUSEBUFFER;
	dInput						= NULL;
	dDevice						= NULL;
}

/*
	Destructor for the MouseInput
*/
MouseInput::~MouseInput()
{

}

/*
	Initialisation of the mouse, setting up the mouse and creation a new mouse-object 
	@param hWnd, HWND needed for setting the cooperatelevel
*/
bool MouseInput::InitMouseInput(HWND hWnd)
{
	//DirectInput8Create should be done only once in manager
	HRESULT result = DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&dInput, NULL);
	if(FAILED(result))
	{
		return false;
	} 

	result = this->dInput->CreateDevice(GUID_SysMouse, &dDevice, NULL);
	if(FAILED(result))
	{
		this->SaveReleaseDevice(); 
		return false;
	}

	result = this->dDevice->SetDataFormat(&c_dfDIMouse);
	if(FAILED(result))
	{
		this->SaveReleaseDevice(); 
		return false;
	}

	result = this->dDevice->SetCooperativeLevel(hWnd, DISCL_EXCLUSIVE | DISCL_FOREGROUND);
	if(FAILED(result))
	{
		this->SaveReleaseDevice(); 
		return false;
	}
	
	return true;
}

/*
	Get mouse input
*/
void MouseInput::GetMouseInput()
{
	if(!SUCCEEDED(this->dDevice->Poll()))
	{
		this->DoAcquire();
	}
	
	this->SetTheMouseData();
}


/*
	Acquire the device
*/
bool MouseInput::DoAcquire()
{
	if(SUCCEEDED(dDevice->Acquire()))
	{
		return true;
	}
	return false;
}

/*
	Set the mouse data
*/
void MouseInput::SetTheMouseData()
{
	dDevice->GetDeviceState(sizeof(DIMOUSESTATE), (void**) &mouseState);
}




/*
	Release the device
*/
void MouseInput::SaveReleaseDevice() 
{ 
	if(this->dInput)
	{ 
		if(this->dDevice)
		{ 
			this->dDevice->Unacquire();
			this->dDevice->Release();
			this->dDevice = NULL;
		} 
		this->dInput->Release();
		this->dInput = NULL;
	} 
} 

/*
	Get the relative x position
*/
float MouseInput::GetRelativeX()
{
	return (float)this->mouseState.lX / this->mouseSensitivity;
}

/*
	Get the relative y position
*/
float MouseInput::GetRelativeY()
{
	return (float)this->mouseState.lY / this->mouseSensitivity;
}





