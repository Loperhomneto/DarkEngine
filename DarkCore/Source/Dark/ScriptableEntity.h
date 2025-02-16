#pragma once
#include "Dark/TimeStep.h"
#include "Entity.h"

namespace Dark
{

	class ScriptableEntity
	{
	public:
		virtual ~ScriptableEntity() {};

		template<typename T>
		T& GetComponent()
		{
			return m_entity.GetComponent<T>();
		}

		//TODO: make these non-virtual
		virtual void OnAttach() = 0;
		virtual void OnUpdate(TimeStep ts) = 0;
		virtual void OnDetach() = 0;
	private:
		Entity m_entity;

		friend class Scene;
	};

}
