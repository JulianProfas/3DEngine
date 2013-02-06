#define DIRECTINPUT_VERSION 0x0800

#include "MouseInput.h"
#include <iostream>

MouseInput::MouseInput( HWND argHwnd )
{
	const int MOUSEBUFFER = 8;

	dipdw.diph.dwSize			= sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize		= sizeof(DIPROPHEADER);
	dipdw.diph.dwObj			= 0;
	dipdw.diph.dwHow			= DIPH_DEVICE;
	dipdw.dwData				= MOUSEBUFFER;
	hwnd						= argHwnd;
	dInput						= NULL;
	dDevice						= NULL;

	InitMouseInput();
}

/**
 * Function:	Mouse::~Mouse()
 * Description:	destructor of the mouse
 */
MouseInput::~MouseInput()
{

}

/**
 * Function:	Mouse::InitMouse()
 * Description:	initialisation of the mouse, setting up the mouse and creation a new mouse-object 
 *				(including aquiring)
 */
bool MouseInput::InitMouseInput()
{
	//DirectInput8Create should be done only once in manager
	HRESULT result = DirectInput8Create( GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&dInput, NULL );
	if( FAILED( result ) )
	{
		return false;
	} 

	result = dInput->CreateDevice( GUID_SysMouse, &dDevice, NULL );
	if( FAILED( result ) )
	{
		SaveReleaseDevice(); 
		return false;
	}

	result = dDevice->SetDataFormat( &c_dfDIMouse );
	if( FAILED( result ) )
	{
		SaveReleaseDevice(); 
		return false;
	}

	result = dDevice->SetCooperativeLevel( hwnd, DISCL_EXCLUSIVE | DISCL_FOREGROUND );
	if( FAILED( result ) )
	{
		SaveReleaseDevice(); 
		return false;
	}

	
	return true;
}

/**
 * Function:	Mouse::GetMouseInput()
 * Description:	Method to see if the mousebuffer can be red or that a aquire is needed
 */
bool MouseInput::GetMouseInput(Scene* s)
{
	if(!SUCCEEDED( dDevice->Poll()))
	{
		DoAcquire();
	}
	
	SetTheMouseBuffer(s);

	return true;
}


/**
 * Function:	Mouse::DoAcquire()
 * Description:	function that aquires the mouse object, just to be sure it does
 *				it five times
 */
bool MouseInput::DoAcquire()
{
	if( SUCCEEDED( dDevice->Acquire() ) )
	{
		return true;
	}
	//std::cout<<"Keyboard acuiring somehow failed"<<std::endl;
	return false;
}

/**
 * Function:	Mouse::SetTheMouseBuffer()
 * Description:	Setting the buffer for the mouse and getting the device-data
 */
void MouseInput::SetTheMouseBuffer(Scene* s)
{
	dDevice->GetDeviceState(sizeof(DIMOUSESTATE), (void**) &mouseState);
}




/**
 * Function:	Mouse::SaveReleaseDevice() 
 * Description:	Cleaning up the mess left if a mouse device is lost
 */
void MouseInput::SaveReleaseDevice() 
{ 
	if( dInput )
	{ 
		if( dDevice )
		{ 
			dDevice->Unacquire();
			dDevice->Release();
			dDevice = NULL;
		} 
		dInput->Release();
		dInput = NULL;
	} 
} 

float MouseInput::GetRelativeX()
{
	return (float)this->mouseState.lX * -0.003f;
}

float MouseInput::GetRelativeY()
{
	return (float)this->mouseState.lY * -0.003f;
}





