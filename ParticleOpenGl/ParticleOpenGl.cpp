#include "Application.h"

int main()
{
	Application App = Application();

	App.Init();

	while (App.IsRunning())
	{
		App.Update();
	}

return 0;
}
