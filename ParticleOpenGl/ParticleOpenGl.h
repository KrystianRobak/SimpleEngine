#include "coordinator.h"
#include "Window.h"


const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


int main()
{
	Coordinator* coordinator = Coordinator::GetCoordinator();

	coordinator->Init();

	Window windowManager;
	windowManager.Init(SCR_WIDTH, SCR_WIDTH, "REngine");

	while(true)
		windowManager.Render();


	windowManager.~Window();

return 0;
}
