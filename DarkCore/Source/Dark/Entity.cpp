#include "dkpch.h"
#include "Entity.h"

namespace Dark
{

	Entity::Entity(entt::entity ent, Scene* scene)
	{
		m_Scene = scene;
		m_entityID = ent;
	}

}
