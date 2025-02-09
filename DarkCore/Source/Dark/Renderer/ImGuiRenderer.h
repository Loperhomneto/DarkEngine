#pragma once
#include "Dark/Window.h"

struct GLFWwindow;

namespace Dark
{

	class ImGuiRenderer
	{
	public:
		void Init(std::shared_ptr<Window> window);
		void Shutdown();

		void StartRendererCall();
		void EndRendererCall();
	};			

}
