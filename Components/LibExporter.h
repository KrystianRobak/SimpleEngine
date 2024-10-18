#pragma once

#ifdef COMPONENTS_EXPORTS
#define COMPONENTS_API __declspec(dllexport)
#else
#define COMPONENTS_API __declspec(dllimport)
#endif