#include "dkpch.h"
#include "Input.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace Dark {

	bool Input::m_blockInputs = false;

	bool Input::isKeyPressed(int keycode)
	{
		if (!m_blockInputs)
		{
			GLFWwindow* window = glfwGetCurrentContext();
			int key = glfwGetKey(window, keycode);

			if (key == GLFW_PRESS || key == GLFW_REPEAT)
			{
				return true;
			}
			return false;
		}
		return false;
	}

	bool Input::isMousePressed(int button)
	{
		if (!m_blockInputs)
		{
			GLFWwindow* window = glfwGetCurrentContext();
			return glfwGetMouseButton(window, button);
		}
		return false;
	}

	std::pair<int, int> Input::GetMousePosition()
	{
		GLFWwindow* window = glfwGetCurrentContext();
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		return std::pair<int, int>(xpos, ypos);
	}

	int Input::GetXPos()
	{
		GLFWwindow* window = glfwGetCurrentContext();
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		return xpos;
	}

	int Input::GetYPos()
	{
		GLFWwindow* window = glfwGetCurrentContext();
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		return ypos;
	}

	double Input::getProgramTime()
	{
		return glfwGetTime();
	}

	int Input::GetWindowWidth()
	{
		GLFWwindow* window = glfwGetCurrentContext();
		int width, height;
		glfwGetWindowSize(window, &width, &height);

		return width;
	}

	int Input::GetWindowHeight()
	{
		GLFWwindow* window = glfwGetCurrentContext();
		int width, height;
		glfwGetWindowSize(window, &width, &height);

		return height;
	}

}


