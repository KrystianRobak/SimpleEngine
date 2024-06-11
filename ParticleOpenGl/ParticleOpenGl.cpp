#include "coordinator.h"
#include "Window.h"
#include "Types.h"

int main()
{
	std::shared_ptr<Coordinator> coordinator = Coordinator::GetCoordinator();

	coordinator->Init();

	Window windowManager;
	windowManager.Init(SCR_WIDTH, SCR_WIDTH, "REngine");

	while(true)
		windowManager.Render();


	windowManager.~Window();

return 0;
}
