#pragma once

#include <bitset>
#include <cstdint>


// ECS
using Entity = std::uint32_t;

const Entity APPLICATION = -1;
const Entity GUI = -2;
const Entity WINDOW = -3;

const Entity MAX_ENTITIES = 60;
const Entity MAX_LIGHT_ENTITIES = 10;
const Entity MAX_OBJECT_ENTITIES = 50;
using ComponentType = std::uint8_t;
const ComponentType MAX_COMPONENTS = 32;
using Signature = std::bitset<MAX_COMPONENTS>;

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


// Input
enum class InputButtons
{
	W,
	A,
	S,
	D,
	Q,
	E
};


// Events
using EventType = std::string;
using ParamId = std::string;

#define METHOD_LISTENER_NO_PARAM(EventType, Listener) EventType, std::bind(&Listener, this)
#define METHOD_LISTENER_ONE_PARAM(EventType, Listener) EventType, std::bind(&Listener, this, std::placeholders::_1)
#define METHOD_LISTENER_TWO_PARAM(EventType, Listener) EventType, std::bind(&Listener, this, std::placeholders::_1, std::placeholders::_2)
#define METHOD_LISTENER_THREE_PARAM(EventType, Listener) EventType, std::bind(&Listener, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)
#define METHOD_LISTENER_FOUR_PARAM(EventType, Listener) EventType, std::bind(&Listener, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4)

#define FUNCTION_LISTENER_ONE_PARAM(EventType, Listener) EventType, std::bind(&Listener, std::placeholders::_1)


namespace Events::Window {
	const EventType QUIT = "Events::Window::QUIT";
	const EventType RESIZED = "Events::Window::RESIZED";
	const EventType INPUT = "Events::Window::INPUT";
}

namespace Events::Window::Input {
	const ParamId INPUT = "Events::Window::Input::INPUT";
}

namespace Events::Window::Resized {
	const ParamId WIDTH = "Events::Window::Resized::WIDTH";
	const ParamId HEIGHT = "Events::Window::Resized::HEIGHT";
}

namespace Events::Application {
	const EventType TOGGLE = "Events::Application::TOGGLE";
	const EventType RECOMPILE_SHADER = "Events::Application::RECOMPILE_SHADER";
	const EventType LIGHT_ENTITY_ADDED = "Events::Application::LIGHT_ENTITY_ADDED";
}
