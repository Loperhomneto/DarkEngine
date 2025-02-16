#pragma once
#include "entt.hpp"

#include "Scene.h"

namespace Dark
{

	class Entity
	{
	public:
		Entity() = default;
		Entity(entt::entity, Scene* scene);

		template<typename T, typename... Args>	
		T& AddComponent(Args&&...args)
		{
			//TODO: add failsafe
			return m_Scene->m_registry.emplace<T>(m_entityID, std::forward<Args>(args)...);
		}

		template<typename T>
		T& GetComponent()
		{
			//TODO: add failsafe
			return m_Scene->m_registry.get<T>(m_entityID);
		}

		template<typename T>
		void RemoveComponent()
		{
			//TODO: add failsafe
			return m_Scene->m_registry.remove<T>(m_entityID);
		}
	private:
		entt::entity m_entityID = entt::null;
		Scene* m_Scene = nullptr;
	};

}
