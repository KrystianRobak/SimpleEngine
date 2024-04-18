//#pragma once
//#include <bitset>
//#include "Entity.h"
//#include <vector>
//
//using ComponentTypeId = std::uint64_t;
//
//inline constexpr ComponentTypeId INVALID_COMPONENT_TYPE_ID = 0;
//inline constexpr std::uint32_t INIT_COMPONENT_POOL_CAPACITY = 100'000;
//inline constexpr std::uint32_t MAX_COMPONENT_TYPES = 64;
//
//using ComponentMask = std::bitset<MAX_COMPONENT_TYPES>;
//
//class ComponentTypeIdHolder
//{
//public:
//	static ComponentTypeId s_componentTypeCounter;
//};
//
//template<class ComponentType>
//inline ComponentTypeId GetComponentTypeId()
//{
//	static ComponentTypeId id = INVALID_COMPONENT_TYPE_ID;
//	if (id == INVALID_COMPONENT_TYPE_ID) 
//	{
//		if (ComponentTypeIdHolder::s_componentTypeCounter<MAX_COMPONENT_TYPES>)
//		{
//			id = ++ComponentTypeIdHolder::s_componentTypeCounter;
//		}
//		else 
//		{
//			return 0;
//		}
//	}
//
//	return id;
//}
//
//template<class ComponentType>
//class ComponentPool
//{
//public:
//	ComponentType& AddComponent();
//	
//	void RemoveComponent(Entity entity);
//	ComponentType& GetComponent(Entity entity);
//	std::vector<ComponentType>& GetComponents();
//	const std::vector<ComponentType>& GetComponents() const;
//	
//private:
//	std::vector<ComponentType> m_components;
//};
//
