#include "KeyboardInput.h"
#include "MouseInput.h"

class InputManager
{
public:
	InputManager();
	~InputManager();
	void AddKeyboardInput(HWND hwnd);
	void AddMouseInput(HWND hwnd);
	void Release();
	void CheckStates();

private:
	KeyboardInput* keyboardInput;
	MouseInput* mouseInput;
};

