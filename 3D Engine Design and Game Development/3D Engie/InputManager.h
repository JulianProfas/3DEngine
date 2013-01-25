
#include "KeyboardInput.h"
#include "MouseInput.h"

#include "Scene.h"
 
class InputManager
{
public:
	InputManager();
	~InputManager();
	void AddKeyboardInput(HWND hwnd);
	void AddMouseInput(HWND hwnd);
	void Release();
	void CheckStates(Scene* s);

private:
	KeyboardInput* keyboardInput;
	MouseInput* mouseInput;
};

