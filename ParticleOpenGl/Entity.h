#pragma once
#include <atomic>

using Entity = std::uint64_t;
inline constexpr Entity INVALID_ENTITY_ID = 0;

inline Entity GenerateEntityId()
{
	static std::atomic<Entity> next{ INVALID_ENTITY_ID + 1 };
	return next.fetch_add(1);
}

