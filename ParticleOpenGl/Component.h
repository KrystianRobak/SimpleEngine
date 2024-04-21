#pragma once
#include <bitset>
#include "Entity.h"
#include <vector>
#include <unordered_map>

using ComponentTypeId = std::uint64_t;

inline constexpr ComponentTypeId INVALID_COMPONENT_TYPE_ID = 0;
inline constexpr std::uint32_t INIT_COMPONENT_POOL_CAPACITY = 100'000;
inline constexpr std::uint32_t MAX_COMPONENT_TYPES = 64;

using ComponentMask = std::bitset<MAX_COMPONENT_TYPES>;

class ComponentTypeIdHolder
{
public:
	static ComponentTypeId s_componentTypeCounter;
};

template<class ComponentType>
inline ComponentTypeId GetComponentTypeId()
{
	static ComponentTypeId id = INVALID_COMPONENT_TYPE_ID;
	if (id == INVALID_COMPONENT_TYPE_ID) 
	{
		if (ComponentTypeIdHolder::s_componentTypeCounter < MAX_COMPONENT_TYPES)
		{
			id = ++ComponentTypeIdHolder::s_componentTypeCounter;
		}
		else 
		{
			return 0;
		}
	}

	return id;
}

struct IComponentPool
{
	virtual ~IComponentPool() = default;

	virtual void Clear() = 0;
	virtual void RemoveComponent(Entity entity) = 0;
	virtual Entity GetEntity(std::uint32_t componentIndex) const = 0;
};


template<class ComponentType>
class ComponentPool : public IComponentPool
{
public:
	ComponentPool()
	{
		m_components.reserve(INIT_COMPONENT_POOL_CAPACITY);
	}

	void Clear() override
	{
		m_components.clear();
		m_entities.clear();
		m_entityToComponentIndex.clear();
	}
	template<typename... Args>
	ComponentType& AddComponent(Entity entity, Args&&... args)
	{
		m_entityToComponentIndex.insert({ entity, m_components.size() });
		m_components.emplace_back(std::forward<Args>(args)...);
		m_entities.emplace_back(entity);
		return m_components.back();
	}
	
	void RemoveComponent(Entity entity) override
	{
		auto it = m_entityToComponentIndex.find(entity);
		if (it == m_entityToComponentIndex.end())
		{
			return;
		}
		
		const std::uint64_t componentIndex = it->second;
		if (componentIndex < m_components.size() - 1) 
		{
			m_components[componentIndex] = std::move(m_components.back());
			m_entities[componentIndex] = std::move(m_entities.back());

			const Entity movedComponentIdex = m_entities.back();
			m_entityToComponentIndex[movedComponentIdex] = componentIndex;
		}

		m_entityToComponentIndex.erase(it);

		if (!m_components.empty()) 
		{
			m_components.pop_back();
			m_entities.pop_back();
		}
	}

	Entity GetEntity(std::uint32_t componentIndex) const override
	{
		return m_entities[componentIndex];
	}

	ComponentType& GetComponent(Entity entity)
	{
		auto it = m_entityToComponentIndex.find(entity);
		if (it == m_entityToComponentIndex.end())
		{
			return;
		}
		return m_components[it->second];

	}

	std::vector<ComponentType>& GetComponents()
	{
		return m_components;
	}

	const std::vector<ComponentType>& GetComponents() const
	{
		return m_components;
	}
	
private:
	std::vector<ComponentType> m_components;
	std::vector<Entity> m_entities;
	std::unordered_map<Entity, std::uint64_t> m_entityToComponentIndex;
};

