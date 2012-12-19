#include "KeyboardInput.h"


class InputManager
{
public:
	InputManager();
	~InputManager();
	void AddKeyboardInput(HWND hwnd);
	void AddMouseInput();
	void Release();
	void CheckStates();

private:
	KeyboardInput* keyboardInput;
};

