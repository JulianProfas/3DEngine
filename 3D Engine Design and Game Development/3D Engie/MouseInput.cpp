#define DIRECTINPUT_VERSION 0x0800

#include "MouseInput.h"
#include <iostream>

struct MouseInput::BufferedMouse
{
	int positionX;
	int positionY;
	int z;
	bool button0;
	bool button1;
	bool button2;
	bool button3;
	bool button4;
	bool button5;
	bool button6;
	bool button7;
}bufferedMouse;

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

	ResetMouseStruct();
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

	result = dDevice->SetProperty( DIPROP_BUFFERSIZE, &dipdw.diph );
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
bool MouseInput::GetMouseInput()
{
	if(!SUCCEEDED( dDevice->Poll()))
	{
		DoAcquire();
	}
	
	SetTheMouseBuffer();

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
	else 
	{
		DoAcquire();		//Try again if it failed
	}
	//std::cout<<"Keyboard acuiring somehow failed"<<std::endl;
	return false;
}

/**
 * Function:	Mouse::SetTheMouseBuffer()
 * Description:	Setting the buffer for the mouse and getting the device-data
 */
void MouseInput::SetTheMouseBuffer()
{
	DIDEVICEOBJECTDATA od;
	DWORD elements = 1;

	HRESULT hr = dDevice->GetDeviceData( sizeof(DIDEVICEOBJECTDATA), &od, &elements, 0 );
	//&elements = number of elements in deviceData. 

	// Switch case to get the data from the mouse
	switch (od.dwOfs) 
	{
		// Mouse horizontal motion
		case DIMOFS_X:
			bufferedMouse.positionX += static_cast<long>(od.dwData);
			std::cout<<"Mouse moved horizontal"<<std::endl;
			break;

		// Mouse vertical motion
		case DIMOFS_Y:
			bufferedMouse.positionY += static_cast<long>(od.dwData);
			std::cout<<"Mouse moved vertical"<<std::endl;
			break;

		// Mouse left button
		case DIMOFS_BUTTON0:
			if ( (long)od.dwData == 0 )
			{
				bufferedMouse.button0 = false;
			}
			else
			{
				bufferedMouse.button0 = true;
				std::cout<<"Mouse button0 pressed"<<std::endl;
			}
			break;

		// Mouse left button
		case DIMOFS_BUTTON1:
			if ( static_cast<long>(od.dwData) == 0 )
			{
				bufferedMouse.button1 = false;
			}
			else
			{
				bufferedMouse.button1 = true;
				std::cout<<"Mouse button0 pressed"<<std::endl;
			}
			break;

		// Mousewheel button
		case DIMOFS_BUTTON2:
			if ( static_cast<long>(od.dwData) == 0 )
			{
				bufferedMouse.button2 = false;
			}
			else
			{
				bufferedMouse.button2 = true;
				std::cout<<"Mouse button0 pressed"<<std::endl;
			}
			break;
		
		// Button 3
		case DIMOFS_BUTTON3:
			if ( static_cast<long>(od.dwData) == 0 )
			{
				bufferedMouse.button3 = false;
			}
			else
			{
				bufferedMouse.button3 = true;
				std::cout<<"Mouse button0 pressed"<<std::endl;
			}
			break;

		// Button 4
		case DIMOFS_BUTTON4:
			if ( static_cast<long>(od.dwData) == 0 )
			{
				bufferedMouse.button4 = false;
			}
			else
			{
				bufferedMouse.button4 = true;
				std::cout<<"Mouse button0 pressed"<<std::endl;
			}
			break;

		// Button 5
		case DIMOFS_BUTTON5:
			if ( static_cast<long>(od.dwData) == 0 )
			{
				bufferedMouse.button5 = false;
			}
			else
			{
				bufferedMouse.button5 = true;
				std::cout<<"Mouse button0 pressed"<<std::endl;
			}
			break;

		// Button 6
		case DIMOFS_BUTTON6:
			if ( static_cast<long>(od.dwData) == 0 )
			{
				bufferedMouse.button6 = false;
			}
			else
			{
				bufferedMouse.button6 = true;
				std::cout<<"Mouse button0 pressed"<<std::endl;
			}
			break;

		// Button 7
		case DIMOFS_BUTTON7:
			if ( static_cast<long>(od.dwData) == 0 )
			{
				bufferedMouse.button7 = false;
			}
			else
			{
				bufferedMouse.button7 = true;
				std::cout<<"Mouse button0 pressed"<<std::endl;
			}
			break;

		// Mouse wheel
		case DIMOFS_Z:
			bufferedMouse.z += static_cast<long>(od.dwData);
			std::cout<<"Mousewheel used"<<std::endl;
			break;
	}
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

void MouseInput::ResetMouseStruct()
{
	bufferedMouse.positionX = 0;
	bufferedMouse.positionY = 0;
	bufferedMouse.z = 0;
	bufferedMouse.button0 = false;
	bufferedMouse.button1 = false;
	bufferedMouse.button2 = false;
	bufferedMouse.button3 = false;
	bufferedMouse.button4 = false;
	bufferedMouse.button5 = false;
	bufferedMouse.button6 = false;
	bufferedMouse.button7 = false;	
}



