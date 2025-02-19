#pragma once
#include "Dark/TimeStep.h"
#include "glm.hpp"
#include "imgui.h"
#include "ScriptableEntity.h"
#include <cstring>

namespace Dark
{

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
			ImGui::Text(Tag.c_str());
			//ImGui::SameLine();
		}
	};

	struct TransformComponent
	{
		glm::vec3 Pos;
		glm::vec2 Size;
		float Rotation;

		TransformComponent(glm::vec2 pos, glm::vec2 size, float rotation = 90.0f)
			: Pos(pos, 0.0f), Size(size), Rotation(rotation) {}
		TransformComponent(glm::vec3 pos, glm::vec2 size, float rotation = 90.0f)
			: Pos(pos), Size(size), Rotation(rotation) {}

		void ImGuiRender()
		{
			ImGui::Text("Pos: %.3f, %.3f, %.3f", Pos.x, Pos.y, Pos.z);
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
			ImGui::Text("Color: %.3f, %.3f, %.3f, %.3f", Color.x, Color.y, Color.z, Color.w);
			ImGui::Text("Texture Name: %s", TexName.c_str());
		}
	};

	struct SpriteComponent
	{
		std::string SpritesheetTexName;
		glm::vec2 SpriteCoords;
		glm::vec2 SpriteSize;

		SpriteComponent(std::string spritesheetTexName, glm::vec2 spriteCoords, glm::vec2 spriteSize = glm::vec2(1.0f, 1.0f))
			: SpritesheetTexName(spritesheetTexName), SpriteCoords(spriteCoords), SpriteSize(spriteSize) {}
		
		void ImGuiRender()
		{
			ImGui::Text("SpritesheetTexName: %s", SpritesheetTexName);
			ImGui::Text("SpriteCoords: %.2f, %.2f", SpriteCoords.x, SpriteCoords.y);
			ImGui::Text("SpriteSize: %s", SpriteSize.x, SpriteSize.y);
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
		}
	};
}