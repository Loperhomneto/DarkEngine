#include "ScenePanel.h"

ScenePanel::ScenePanel(std::shared_ptr<Scene> scene)
{
	setContext(scene);
}

void ScenePanel::setContext(std::shared_ptr<Scene> scene)
{
	m_context = scene;
}

void ScenePanel::OnImGuiRender()
{
	ImGui::Begin("Scene Panel");

	auto view = m_context->m_registry.view<TagComponent>();
	for (auto entity : view)
	{
		Entity ent = Entity(entity, m_context.get());
		TreeNode(ent);
	}

	ImGui::End();
}

#define IMGUI_SET_COMPONENTS(componentName) if (entity.HasComponent<componentName>())\
{\
	ImGui::PushID(i);\
	if (ImGui::TreeNode("", #componentName))\
	{\
		entity.GetComponent<componentName>().ImGuiRender();\
\
		ImGui::TreePop();\
	}\
	ImGui::PopID();\
	i++;\
}

void ScenePanel::TreeNode(Entity entity)
{
	auto& tagComp = entity.GetComponent<TagComponent>();

	ImGui::TreeNodeEx(tagComp.Tag.c_str(), ImGuiTreeNodeFlags_DefaultOpen);

	int i = 0;
	IMGUI_SET_COMPONENTS(TransformComponent)
	IMGUI_SET_COMPONENTS(RendererComponent)
	IMGUI_SET_COMPONENTS(SpriteComponent)
	IMGUI_SET_COMPONENTS(NativeScriptComponent)

	ImGui::TreePop();
}
