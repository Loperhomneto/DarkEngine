#pragma once
#include "Dark/TimeStep.h"
#include "glm.hpp"
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
	};

	struct TransformComponent
	{
		glm::vec2 Pos;
		glm::vec2 Size;
		float Rotation;

		TransformComponent(glm::vec2 pos, glm::vec2 size, float rotation = 90.0f)
			: Pos(pos), Size(size), Rotation(rotation) {}
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
	};

	struct Sprite
	{
		std::string SpritesheetTexName;
		glm::vec2 SpriteCoords;
		glm::vec2 SpriteSize;

		Sprite(std::string spritesheetTexName, glm::vec2 spriteCoords, glm::vec2 spriteSize = glm::vec2(1.0f, 1.0f))
			: SpritesheetTexName(spritesheetTexName), SpriteCoords(spriteCoords), SpriteSize(spriteSize) {}
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
	};
}