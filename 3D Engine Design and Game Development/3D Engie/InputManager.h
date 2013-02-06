#ifndef ENGIE_INPUTMANAGER_H
#define ENGIE_INPUTMANAGER_H

#include "KeyboardInput.h"
#include "MouseInput.h"
#include "Logger.h"

class InputManager
{
public:
	//Constructor for an InputManager object
	InputManager();
	//Destructor for an InputManager object
	~InputManager();
	//Creates the KeyBoardInput
	void AddKeyboardInput();
	//Creates the MouseInput
	void AddMouseInput();
	//Releases the keyboardinput and mouseinput
	void Release();
	//Update mouse states
	void UpdateStates();
	//Get the keyboardInput
	KeyboardInput* GetKeyboard();
	//Get the mouseInput
	MouseInput* GetMouse();
private:
	//KeyboardInput object
	KeyboardInput* keyboardInput;
	//MouseInput object
	MouseInput* mouseInput;
};

#endif
