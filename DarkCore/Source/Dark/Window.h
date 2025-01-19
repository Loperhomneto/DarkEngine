#pragma once
#include "Event.h"
#include <string>

struct GLFWwindow;

namespace Dark
{
	class Window
	{
	public:
		Window(std::function<void(Event&)> func, std::string name, int width, int height);

		int getScreenWidth() { return m_data.SCR_WIDTH; }
		int getScreenHeight() { return m_data.SCR_HEIGHT; }

		void end();

		void ShutDown();
	private:
		GLFWwindow* window;

		struct DATA
		{
			int SCR_WIDTH;
			int SCR_HEIGHT;

			std::function<void(Event&)> eventCallback;
		} m_data;
	};

}



