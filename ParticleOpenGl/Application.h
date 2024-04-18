#pragma once
#include <string>
#include "Window.h"

class Application
{
public:
	Application(const std::string& app_name);

	static Application& Instance() { return *sInstance; }

	void loop();

private:
	static Application* sInstance;

	std::unique_ptr<Window> window;
};

