#include "Logger.h"
#include "Window.h"

int main()
{

	Logger::GetInstance()->Write("billy bob");

	Window* w = new Window(250, 150, 400, 400, "Homo blok");
	w->Show();

	return 0;
};