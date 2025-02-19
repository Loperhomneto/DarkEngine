#pragma once
#include "entt.hpp"
#include "glm.hpp"

#include "TimeStep.h"

class ScenePanel;

namespace Dark
{
	class Entity;

	class Scene
	{
	public:
		Scene();
		~Scene();

		std::shared_ptr<Entity> CreateEntity(std::string name = "Unnamed Component", 
			glm::vec2 pos = glm::vec2(0.0f, 0.0f), glm::vec2 size = glm::vec2(1.0f, 1.0f));
		std::shared_ptr<Entity> CreateEntity(std::string name,
			glm::vec3 pos, glm::vec2 size = glm::vec2(1.0f, 1.0f));

		void OnUpdate(TimeStep ts);
	private:
		entt::registry m_registry;

		friend class Entity;
		friend class ScenePanel;
	};

}
