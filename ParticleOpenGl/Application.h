#pragma once
#include <string>
#include "Window.h"
#include "Coordinator.h"

class Application
{
public:
	Application(const std::string& app_name);

	static Application& Instance() { return *sInstance; }

	void loop();

	void Init();

	void GameLoop();

private:
	static Application* sInstance;
	Coordinator coordinator;
	std::unique_ptr<Window> window;
	float dt = 0.0f;
};

