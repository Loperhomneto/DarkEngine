#pragma once
#include "entt.hpp"

#include "Scene.h"
#include "Logger.h"

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
			return m_Scene->m_registry.emplace_or_replace<T>(m_entityID, std::forward<Args>(args)...);
		}

		template<typename T>
		T& GetComponent()
		{
			//TODO: make try_get
			if (m_Scene->m_registry.all_of<T>(m_entityID))
				return m_Scene->m_registry.get<T>(m_entityID);
			else
				Logger::error("Does not have the component within the entity");
		}

		template<typename T>
		void RemoveComponent()
		{
			return m_Scene->m_registry.remove<T>(m_entityID);
		}
	private:
		entt::entity m_entityID = entt::null;
		Scene* m_Scene = nullptr;
	};

}
