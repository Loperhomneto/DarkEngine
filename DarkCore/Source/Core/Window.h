#pragma once
#include "Event.h"
#include <string>

struct GLFWwindow;

namespace Dark
{
	class Window
	{
	public:
		Window(int FPS, std::function<void(Event&)> func, std::string name);

		int getScreenWidth() { return SCR_WIDTH; }
		int getScreenHeight() { return SCR_HEIGHT; }

		void OnUpdate();

		void ShutDown();
	private:
		void SetEventBindFuncs(std::function<void(Event&)> func);
	private:
		int fps;

		int SCR_WIDTH = 800;
		int SCR_HEIGHT = 600;

		GLFWwindow* window;

		double timeprev = 0.0;
		double timenext = 0.0;

		std::function<void(Event&)> eventCallback;
	};

}



