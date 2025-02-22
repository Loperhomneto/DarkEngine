#pragma once
#include "Dark/TimeStep.h"
#include "glm.hpp"
#include "gtc/type_ptr.hpp"
#include "imgui.h"
#include "ScriptableEntity.h"
#include <cstring>

namespace Dark
{

	void ImGuiVec2Helper(const std::string& label, glm::vec2& values);
	void ImGuiVec3Helper(const std::string& label, glm::vec3& values);

	struct TagComponent
	{
		std::string Tag;

		TagComponent(const char* tag)
			: Tag(tag) {}
		TagComponent(std::string tag)
			: Tag(tag) {
		}

		void ImGuiRender()
		{
			if (Tag.empty())
			{
				Logger::warn("Tag Component has an empty tag!");
				
			}
			else
			{
				if (ImGui::CollapsingHeader(Tag.c_str(), ImGuiTreeNodeFlags_DefaultOpen))
				{
					ImGui::Text("Entity Name: ");
					ImGui::SameLine();

					char buffer[256];
					memset(buffer, 0, sizeof(buffer));
					strcpy_s(buffer, sizeof(buffer), Tag.c_str());
					if (ImGui::InputText("##EntityName", buffer, sizeof(buffer)))
					{
						Tag = std::string(buffer);
					}
				}
			}
		}
	};

	struct TransformComponent
	{
		glm::vec3 Pos;
		glm::vec2 Size;
		float Rotation;

		TransformComponent(glm::vec2 pos, glm::vec2 size, float rotation = 0.0f)
			: Pos(pos, 0.0f), Size(size), Rotation(rotation) {}
		TransformComponent(glm::vec3 pos, glm::vec2 size, float rotation = 0.0f)
			: Pos(pos), Size(size), Rotation(rotation) {}

		void ImGuiRender()
		{
			if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen))
			{
				ImGuiVec3Helper("Pos: ", Pos);

				ImGuiVec2Helper("Size: ", Size);

				//Rotation
				ImGui::Text("Rotation: ");
				ImGui::SameLine();
				ImGui::SetNextItemWidth(75);
				ImGui::DragFloat("##Rotation", &Rotation);
			}
		}
	};

	struct RendererComponent
	{
		glm::vec4 Color;
		std::string TexName = "None";

		RendererComponent(glm::vec4 color)
			: Color(color) {}
		RendererComponent(std::string texName, glm::vec4 color = glm::vec4(1.0f))
			: Color(color), TexName(texName) {}
		RendererComponent(const char* texName, glm::vec4 color = glm::vec4(1.0f))
			: Color(color), TexName(texName) {}
		RendererComponent(std::string texName, glm::vec3 color)
			: Color(color, 1.0f), TexName(texName) {}
		RendererComponent(const char* texName, glm::vec3 color)
			: Color(color, 1.0f), TexName(texName) {}

		void ImGuiRender()
		{
			if (ImGui::CollapsingHeader("Renderer Component", ImGuiTreeNodeFlags_DefaultOpen))
			{
				ImGui::Text("Texture Name: ");
				ImGui::SameLine();

				char buffer[256];
				memset(buffer, 0, sizeof(buffer));
				strcpy_s(buffer, sizeof(buffer), TexName.c_str());
				if (ImGui::InputText("##TexName", buffer, sizeof(buffer)))
				{
					TexName = std::string(buffer);
				}

				ImGui::PushID("RendererComponentColor");
				ImGui::ColorEdit4("Color", glm::value_ptr(Color));
				ImGui::PopID();
			}
		}
	};

	struct SpriteComponent
	{
		std::string SpritesheetTexName;
		glm::vec2 SpriteCoords;
		glm::vec2 SpriteSize;
		glm::vec4 Color;

		SpriteComponent(std::string spritesheetTexName, glm::vec2 spriteCoords, glm::vec2 spriteSize = glm::vec2(1.0f, 1.0f), glm::vec4 color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f))
			: SpritesheetTexName(spritesheetTexName), SpriteCoords(spriteCoords), SpriteSize(spriteSize), Color(color) {}
		
		void ImGuiRender()
		{
			if (ImGui::CollapsingHeader("Sprite Component", ImGuiTreeNodeFlags_DefaultOpen))
			{
				ImGui::Text("Texture Name: ");
				ImGui::SameLine();

				char buffer[256];
				memset(buffer, 0, sizeof(buffer));
				strcpy_s(buffer, sizeof(buffer), SpritesheetTexName.c_str());
				if (ImGui::InputText("##SpriteSheetName", buffer, sizeof(buffer)))
				{
					SpritesheetTexName = std::string(buffer);
				}

				ImGuiVec2Helper("SpriteCoords: ", SpriteCoords);
				ImGuiVec2Helper("SpriteSize: ", SpriteSize);
				
				ImGui::PushID("SpriteComponentColor");
				ImGui::ColorEdit4("Color", glm::value_ptr(Color));
				ImGui::PopID();
			}
		}
	};

	struct NativeScriptComponent
	{
		ScriptableEntity* Instance = nullptr;

		NativeScriptComponent(ScriptableEntity* instance)
		{
			Instance = instance;
			Instance->OnAttach();
		}

		//template<typename T>
		//void Bind()
		//{
		//	Instance = static_cast<ScriptableEntity*>(new T);
		//	Instance->OnAttach();
		//}

		~NativeScriptComponent()
		{
			Instance->OnDetach();
			delete Instance;
			Instance = nullptr;
		}

		void ImGuiRender()
		{
			if (ImGui::CollapsingHeader("Native Script Component", ImGuiTreeNodeFlags_DefaultOpen))
			{
			}
		}
	};
}