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

	std::shared_ptr<Entity> Scene::CreateEntity(std::string name, glm::vec3 pos, glm::vec2 size)
	{
		std::shared_ptr<Entity> ent = std::make_shared<Entity>(m_registry.create(), this);
		ent->AddComponent<TagComponent>(name.c_str());
		ent->AddComponent<TransformComponent>(pos, size);

		return ent;
	}

	void Scene::OnUpdate(TimeStep ts)
	{
		auto group = m_registry.group<RendererComponent>(entt::get<TransformComponent>, entt::exclude<SpriteComponent>);
		for (auto entity : group)
		{
			auto& transformComp = group.get<TransformComponent>(entity);
			auto& rendererComp = group.get<RendererComponent>(entity);

			if (Renderer2D::ValidateTexture(rendererComp.TexName))
			{
				Renderer2D::Draw2DRotatedQuad(transformComp.Pos, transformComp.Size, transformComp.Rotation, rendererComp.TexName, rendererComp.Color);
			}
			else
			{
				Renderer2D::Draw2DRotatedQuad(transformComp.Pos, transformComp.Size, transformComp.Rotation, rendererComp.Color);
			}
		}

		auto view = m_registry.view<NativeScriptComponent>();
		for (auto entity : view)
		{
			auto& nativeScriptComp = view.get<NativeScriptComponent>(entity);

			nativeScriptComp.Instance->m_entity = { entity, this } ;
			nativeScriptComp.Instance->OnUpdate(ts);
		}

		auto group2 = m_registry.group<SpriteComponent>(entt::get<TransformComponent>);
		for (auto entity : group2)
		{
			auto& transformComp = group2.get<TransformComponent>(entity);
			auto& spriteComp = group2.get<SpriteComponent>(entity);

			if (m_registry.all_of<RendererComponent>(entity))
			{
				auto& rendererComp = m_registry.get<RendererComponent>(entity);
				Renderer2D::DrawSprite(transformComp.Pos, transformComp.Size, spriteComp.SpritesheetTexName, spriteComp.SpriteCoords, spriteComp.SpriteSize, rendererComp.Color);
			}
			else
			{
				Renderer2D::DrawSprite(transformComp.Pos, transformComp.Size, spriteComp.SpritesheetTexName, spriteComp.SpriteCoords, spriteComp.SpriteSize);
			}
		}

		
	}

}