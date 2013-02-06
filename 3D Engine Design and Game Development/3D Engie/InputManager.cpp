#include "InputManager.h"

/*
	Constructor for an InputManager object
*/
InputManager::InputManager()
{
	Logger::GetInstance()->Write("InputManager created");
}

/*
	Destructor for an InputManager object
*/
InputManager::~InputManager()
{
	this->Release();
	Logger::GetInstance()->Write("InpuntManager destroyed");
}

/*
	Creates the keyboardInput
*/
void InputManager::AddKeyboardInput()
{
	this->keyboardInput = new KeyboardInput();
	Logger::GetInstance()->Write("KeyboardInput created");
}

/*
	Creates the mouseInput
*/
void InputManager::AddMouseInput()
{
	this->mouseInput = new MouseInput(-500);
	Logger::GetInstance()->Write("MouseInput created");
}

/*
	Safely releases keyboardInput and mouseInput
*/
void InputManager::Release()
{
	this->keyboardInput->SaveReleaseDevice();
	this->mouseInput->SaveReleaseDevice();
	Logger::GetInstance()->Write("Input has been safely released");
}

/*
	Update the mouse data
*/
void InputManager::UpdateStates()
{
	this->mouseInput->GetMouseInput();
}

/*
	Get the keyBoardInput
*/
KeyboardInput* InputManager::GetKeyboard()
{
	return this->keyboardInput;
}

/*
	Get the mouseInput
*/
MouseInput* InputManager::GetMouse()
{
	return this->mouseInput;
}
