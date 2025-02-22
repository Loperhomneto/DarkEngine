#include "dkpch.h"
#include "Components.h"

namespace Dark
{
	void ImGuiVec2Helper(const std::string& label, glm::vec2& values)
	{
		ImGui::PushID(label.c_str());

		ImGui::Text(label.c_str());

		//X
		ImGui::SameLine();
		ImGui::PushStyleColor(ImGuiCol_Button, { 0.0f, 0.0f, 0.6f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 0.0f, 0.0f, 0.8f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, { 0.0f, 0.0f, 1.0f, 1.0f });
		ImGui::Button("X");
		ImGui::PopStyleColor(3);

		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 0.0f, 0.0f });
		ImGui::SameLine();
		ImGui::SetNextItemWidth(75);
		ImGui::DragFloat("##X", &values.x, 0.01f);
		ImGui::PopStyleVar(1);

		//Y
		ImGui::SameLine();
		ImGui::PushStyleColor(ImGuiCol_Button, { 0.0f, 0.6f, 0.0f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 0.0f, 0.8f, 0.0f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, { 0.0f, 1.0f, 0.0f, 1.0f });
		ImGui::Button("Y");
		ImGui::PopStyleColor(3);

		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 0.0f, 0.0f });
		ImGui::SameLine();
		ImGui::SetNextItemWidth(75);
		ImGui::DragFloat("##Y", &values.y, 0.01f);
		ImGui::PopStyleVar(1);

		ImGui::PopID();
	}

	void ImGuiVec3Helper(const std::string& label, glm::vec3& values)
	{
		ImGui::PushID(label.c_str());

		ImGui::Text(label.c_str());

		//X
		ImGui::SameLine();
		ImGui::PushStyleColor(ImGuiCol_Button, { 0.0f, 0.0f, 0.6f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 0.0f, 0.0f, 0.8f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, { 0.0f, 0.0f, 1.0f, 1.0f });
		ImGui::Button("X");
		ImGui::PopStyleColor(3);

		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 0.0f, 0.0f });
		ImGui::SameLine();
		ImGui::SetNextItemWidth(75);
		ImGui::DragFloat("##X", &values.x, 0.01f);
		ImGui::PopStyleVar(1);

		//Y
		ImGui::SameLine();
		ImGui::PushStyleColor(ImGuiCol_Button, { 0.0f, 0.6f, 0.0f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 0.0f, 0.8f, 0.0f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, { 0.0f, 1.0f, 0.0f, 1.0f });
		ImGui::Button("Y");
		ImGui::PopStyleColor(3);

		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 0.0f, 0.0f });
		ImGui::SameLine();
		ImGui::SetNextItemWidth(75);
		ImGui::DragFloat("##Y", &values.y, 0.01f);
		ImGui::PopStyleVar(1);

		//Pos Z
		ImGui::SameLine();
		ImGui::PushStyleColor(ImGuiCol_Button, { 0.6f, 0.0f, 0.0f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 0.8f, 0.0f, 0.0f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, { 1.0f, 0.0f, 0.0f, 1.0f });
		ImGui::Button("Z");
		ImGui::PopStyleColor(3);

		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 0.0f, 0.0f });
		ImGui::SameLine();
		ImGui::SetNextItemWidth(75);
		ImGui::DragFloat("##Z", &values.z, 0.01f);
		ImGui::PopStyleVar(1);

		ImGui::PopID();
	}

}