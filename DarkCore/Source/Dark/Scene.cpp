#include "dkpch.h"
#include "Scene.h"

#include "Entity.h"
#include "Components.h"
#include "Renderer/Renderer2D.h"

namespace Dark
{

	Scene::Scene()
	{
	}

	Scene::~Scene()
	{
	}

	std::shared_ptr<Entity> Scene::CreateEntity(std::string name, glm::vec2 pos, glm::vec2 size)
	{
		std::shared_ptr<Entity> ent = std::make_shared<Entity>(m_registry.create(), this);
		ent->AddComponent<TagComponent>(name.c_str());
		ent->AddComponent<TransformComponent>(pos, size);

		return ent;
	}

	void Scene::OnUpdate(TimeStep ts)
	{
		auto group = m_registry.group<TransformComponent>(entt::get<RendererComponent>);

		for (auto entity : group)
		{
			auto& transformComp = group.get<TransformComponent>(entity);
			auto& rendererComp = group.get<RendererComponent>(entity);

			if (rendererComp.TexName == "None")
			{
				Renderer2D::Draw2DRotatedQuad(transformComp.Pos, transformComp.Size, transformComp.Rotation, rendererComp.Color);
			}
			else
			{
				Renderer2D::Draw2DRotatedQuad(transformComp.Pos, transformComp.Size, transformComp.Rotation, rendererComp.TexName, rendererComp.Color);
			}
		}

		auto view = m_registry.view<NativeScriptComponent>();

		for (auto entity : view)
		{
			auto& nativeScriptComp = view.get<NativeScriptComponent>(entity);

			nativeScriptComp.Instance->m_entity = { entity, this } ;
			nativeScriptComp.Instance->OnUpdate(ts);
		}
	}

}