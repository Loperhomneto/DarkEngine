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

	int i = 0;
	auto view = m_context->m_registry.view<TagComponent>();
	for (auto entity : view)
	{
		Entity ent = Entity(entity, m_context.get());

		auto& tagComp = ent.GetComponent<TagComponent>();

		//ScenePanel ImGui Interface
		ImGui::PushID(i);
		if (ImGui::TreeNode("", tagComp.Tag.c_str()))
		{
			if (ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
			{
				selectedEntity = ent;
				m_OpenPropertiesPanel = true;
			}

			ImGui::TreePop();
		}

		if (ImGui::BeginPopupContextItem()) // <-- use last item id as popup id
		{
			ImGui::Text("Entity Name: ");
			ImGui::SameLine();

			char buffer[256];
			memset(buffer, 0, sizeof(buffer));
			strcpy_s(buffer, sizeof(buffer), tagComp.Tag.c_str());
			if (ImGui::InputText("##TagName", buffer, sizeof(buffer)))
			{
				tagComp.Tag = std::string(buffer);
			}

			if (ImGui::Button("Close") || ImGui::IsKeyDown(ImGuiKey_Escape) || ImGui::IsKeyDown(ImGuiKey_Enter))
				ImGui::CloseCurrentPopup();

			if (ImGui::Button("Open Properties Panel"))
			{
				selectedEntity = ent;
				m_OpenPropertiesPanel = true;

				ImGui::CloseCurrentPopup();
			}

			ImGui::EndPopup();
		}
		ImGui::SetItemTooltip("Right-click to rename, Double-Click to open Properties");

		ImGui::PopID();
		i++;
	}

	ImGui::End();

	OpenPropertiesPanelUI();
}

void ScenePanel::OpenPropertiesPanelUI()
{
	if (m_OpenPropertiesPanel)
	{
		ImGui::Begin("Properties Panel");

		if (selectedEntity)
		{
			if (selectedEntity.HasComponent<TagComponent>())
			{
				auto& tagComp = selectedEntity.GetComponent<TagComponent>();
				tagComp.ImGuiRender();
			}
			if (selectedEntity.HasComponent<TransformComponent>())
			{
				auto& transformComp = selectedEntity.GetComponent<TransformComponent>();
				transformComp.ImGuiRender();
			}
			if (selectedEntity.HasComponent<RendererComponent>())
			{
				auto& rendererComp = selectedEntity.GetComponent<RendererComponent>();
				rendererComp.ImGuiRender();
			}
			if (selectedEntity.HasComponent<SpriteComponent>())
			{
				auto& spriteComp = selectedEntity.GetComponent<SpriteComponent>();
				spriteComp.ImGuiRender();
			}
			if (selectedEntity.HasComponent<NativeScriptComponent>())
			{
				auto& nativeScriptComp = selectedEntity.GetComponent<NativeScriptComponent>();
				nativeScriptComp.ImGuiRender();
			}
		}

		ImGui::End();
	}
}
