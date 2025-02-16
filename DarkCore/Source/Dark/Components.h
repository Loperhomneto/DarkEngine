#pragma once
#include "Dark/TimeStep.h"
#include "glm.hpp"
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

		TransformComponent(glm::vec2 pos, glm::vec2 size, float rotation = 0.0f)
			: Pos(pos), Size(size), Rotation(rotation) {
		}
	};

	struct RendererComponent
	{
		glm::vec4 Color;
		std::string TexName;

		RendererComponent(glm::vec4 color, std::string texName = std::string("None"))
			: Color(color), TexName(texName) {}
		RendererComponent(glm::vec4 color, const char* texName)
			: Color(color), TexName(texName) {
		}
	};

	struct NativeScriptComponent
	{
		virtual void OnAttach();
		virtual void OnUpdate(TimeStep ts);
		virtual void OnDetach();
	};
}