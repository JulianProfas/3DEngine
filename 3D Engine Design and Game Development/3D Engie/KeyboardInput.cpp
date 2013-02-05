#define DIRECTINPUT_VERSION 0x0800
#include "KeyboardInput.h"

#include <iostream>


#define KEYDOWN(name, key) (name[key] & 0x80) 

/**
 * Function:	Keyboard::Keyboard()
 * Description:	Empty keyboard constructor
 */
KeyboardInput::KeyboardInput()
{
	
}

/**
 * Function:	Keyboard::Keyboard(...)
 * Description:	Keyboard constructor
 * @ param hWnd:
 *   Pointer to windowHandle, used to set the "SetCooperativeLevel" 
 */
KeyboardInput::KeyboardInput(HWND argHwnd)
{
	dInput = NULL;			
	dDevice = NULL;		
	hwnd = argHwnd;

    InitKeyboardInput();
}


/**
 * Function:	Keyboard::~Keyboard()
 * Description:	Keyboard destructor
 */
KeyboardInput::~KeyboardInput()
{

}


/**
 * Function:	Keyboard::InitKeyboard()
 * Description:	initializing the keyboard (creating the device and setting the coopertive level)
 */
bool KeyboardInput::InitKeyboardInput()
{
	//DirectInput8Create should be done only once in manager
	HRESULT hr = DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&dInput, NULL);
	if FAILED( hr ) 
	{
		return false; 
	}

	hr = dInput->CreateDevice( GUID_SysKeyboard, &dDevice, NULL );
	if FAILED( hr ) 
	{ 
		SaveReleaseDevice(); 
		return false; 
	}

	hr = dDevice->SetDataFormat( &c_dfDIKeyboard ); 
	if FAILED( hr ) 
	{ 
		SaveReleaseDevice(); 
		return false; 
	} 

	hr = dDevice->SetCooperativeLevel( hwnd, DISCL_EXCLUSIVE | DISCL_FOREGROUND );
	if FAILED( hr )
	{ 
		SaveReleaseDevice(); 
		return false; 
	} 

	return true; 
}

/**
 * Function:	Keyboard::saveReleaseDevice() 
 * Description:	Cleaning up the mess left if a keyboard is lost
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


/**
 * Function:	Keyboard::ProcessKBInput(...)
 * Description:	Method to see if the keyboardbuffer can be red or that a aquire is needed
 * @ param argIsToggle
 *	 Boolean to see if the key that is pressed a togglebutton is
 * @ param argKeyIsPressed
 *	 Byte containing the key that must be checked
 */
bool KeyboardInput::ProcessKBInput( byte argKeyIsPressed ) 
{ 
	if(!SUCCEEDED( dDevice->Poll() ))
	{
		DoAcquire();
	}
	
	byte keyBuffer[256]; 

	dDevice->GetDeviceState( sizeof(keyBuffer) , (LPVOID)&keyBuffer);
	
	// Check if keybuffer contains given key
	int pressed = KEYDOWN(keyBuffer, argKeyIsPressed );

	// pressed == 0 or 128 (0x80); meaning false or true
	if( pressed == 0 )
	{
		return false;
	}
	else
	{
		return true;
	}
}

/**
 * Function:	Keyboard::DoAcquire()
 * Description:	Aquiring the device, multiple times to make sure it gets it
 */
bool KeyboardInput::DoAcquire()
{
	if( SUCCEEDED( dDevice->Acquire() ) )
	{
		return true;
	}
	return false;
}

void KeyboardInput::CheckKeyPressed(Scene* s)
{
	
}