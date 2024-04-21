#pragma once
#include <unordered_map>
#include "Component.h"
#include <memory>

class Scene
{
private:
	std::unordered_map<ComponentTypeId, std::shared_ptr<IComponentPool>> m_componentPools;
	std::unordered_map<Entity, ComponentMask> m_entities;
public:
	Entity CreateEntity()
	{
		const Entity id = GenerateEntityId();
		m_entities.insert({ id, ComponentMask() });
		return id;
	}

	const std::unordered_map<Entity, ComponentMask>& GetEntites() const
	{
		return m_entities;
	}

	void DestroyEntites(Entity entity)
	{
		auto entityId = m_entities.find(entity);

		if (entityId != m_entities.end())
		{
			const auto& ComponentMask = entityId->second;
			for (size_t i = 0; i < ComponentMask.size(); i++)
			{
				if (ComponentMask.test(i))
				{
					m_componentPools[i]->RemoveComponent(entity);
				}
			}
		}
	}

	template<typename ComponentType>
	void RegisterComponent() 
	{
		const ComponentTypeId componentTypeId = GetComponentTypeId<ComponentType>();
		auto it = m_componentPools.find(componentTypeId);
		if (it != m_componentPools.end()) 
		{
			m_componentPools.insert({ componentTypeId, std::shared_ptr<ComponentPool<ComponentType>>() });
		}
		else 
		{
		}
	}

	template<typename ComponentType, typename... Args>
	ComponentType& AddComponent(Entity entity, Args&& ...args)
	{
		const ComponentTypeId componentTypeId = GetComponentTypeId<ComponentType>();

		auto it = m_componentPools.find(componentTypeId);

		auto entityIt = m_entities.find(entity);

		entityIt->second.set(componentTypeId);

		return std::static_pointer_cast<ComponentPool<ComponentType>>(it->second)->AddComponent(entity, std::forward<Args>(args)...);
	}


	template<typename ComponentType>
	ComponentType& AddComponent(Entity entity, ComponentType&& component)
	{
		const ComponentTypeId componentTypeId = GetComponentTypeId<ComponentType>();

		auto it = m_componentPools.find(componentTypeId);

		auto entityIt = m_entities.find(entity);

		entityIt->second.set(componentTypeId);

		return std::static_pointer_cast<ComponentPool<ComponentType>>(it->second)->AddComponent(entity, std::forward<ComponentType>(component));
	};

	template<typename ComponentType>
	void RemoveComponent(Entity entity)
	{
		auto entityIt = m_entities.find(entity);

		const ComponentTypeId componentTypeId = GetComponentTypeId<ComponentType>();

		auto it = m_componentPools.find(componentTypeId);

		entityIt->second.set(componentTypeId, false);
		it->second->RemoveComponent(entity);
	}

	template<typename ComponentType>
	bool HasComponent(Entity entity)
	{
		auto entityIt = m_entities.find(entity);

		const ComponentTypeId componentTypeId = GetComponentTypeId<ComponentType>();
		return entityIt->second.test(componentTypeId);
	}

	template<typename ComponentType>
	ComponentType& GetComponent(Entity entity)
	{
		auto entityIt = m_entities.find(entity);

		const ComponentTypeId componentTypeid = GetComponentTypeId<ComponentType>();

		auto it = m_componentPools.find(componentTypeid);

		return std::static_pointer_cast<ComponentPool<ComponentType>>(it->second)->GetComponent(entity);
	}

	template<typename ComponentType>
	std::vector<ComponentType>& GetComponents() const
	{
		const ComponentTypeId componentTypeId = GetComponentTypeId<ComponentType>();
		auto it = m_componentPools.find(componentTypeId);

		return std::static_pointer_cast<ComponentPool<ComponentType>>(it->second)->GetComponents();
	}

	template<typename ComponentType>
	bool IsComponentTypeRegistered() const
	{
		const ComponentTypeId componentTypeId = GetComponentTypeId<ComponentType>();
		auto it = m_componentPools.find(componentTypeId);

		return it != m_componentPools.end();
	}

	template<typename ComponentType>
	std::shared_ptr<ComponentPool<ComponentType>> GetComponentPool()
	{
		const ComponentTypeId componentTypeid = GetComponentTypeId<ComponentType>();
		auto it = m_componentPools.find(componentTypeid);

		return std::static_pointer_cast<ComponentPool<ComponentType>>(it->second);
	}

	template<typename ComponentType>
	Entity GetEntity(std::uint32_t componentIndex) const
	{
		const ComponentTypeId componentTypeId = GetComponentTypeId<ComponentType>();
		auto it = m_componentPools.find(componentTypeId);

		return it->second->GetEntity(componentIndex);
	}
};

