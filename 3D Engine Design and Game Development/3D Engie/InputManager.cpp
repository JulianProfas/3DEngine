#include "InputManager.h"
#include "Logger.h"

/*
	Constructor.
*/
InputManager::InputManager()
{

	Logger::GetInstance()->Write("InputManager aangemaakt");
}

/*
	Destructor.
*/
InputManager::~InputManager()
{
	Release();
	Logger::GetInstance()->Write("InpuntManager verwijderd");
}

/*
	Creates the keyboardInput
*/
void InputManager::AddKeyboardInput(HWND hwnd)
{
	keyboardInput = new KeyboardInput(hwnd);
	Logger::GetInstance()->Write("KeyboardInput aangemaakt");
}

/*
	Creates the mouseInput
*/
void InputManager::AddMouseInput(HWND hwnd)
{
	mouseInput = new MouseInput(hwnd);
	Logger::GetInstance()->Write("MouseInput aangemaakt");
}

/*
	Safely releases keyboardInput and mouseInput
*/
void InputManager::Release()
{
	keyboardInput->SaveReleaseDevice();
	mouseInput->SaveReleaseDevice();
	Logger::GetInstance()->Write("Input has been safely released");
}

void InputManager::CheckStates(Scene* s)
{
	keyboardInput->CheckKeyPressed(s);
	mouseInput->GetMouseInput(s);
}
