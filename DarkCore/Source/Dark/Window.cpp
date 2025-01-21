#include "Window.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Dark/Core.h"
#include <iostream>

namespace Dark
{

	Window::Window(std::function<void(Event&)> func, std::string name, int width, int height)
	{
		m_data.SCR_WIDTH = width;
		m_data.SCR_HEIGHT = height;

		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		window = glfwCreateWindow(m_data.SCR_WIDTH, m_data.SCR_HEIGHT, name.c_str(), NULL, NULL);

		if (window == NULL)
		{
			Logger::error("Failed to create GLFW window");
			glfwTerminate();
		}
		glfwMakeContextCurrent(window);
		//glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			Logger::error("Failed to initialize GLAD");
		}

		m_data.eventCallback = func;

		glfwSetWindowUserPointer(window, &m_data);

		glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				DATA data = *(DATA*)glfwGetWindowUserPointer(window);
				std::function<void(Event&)> callback = data.eventCallback;

				KeyInputEvent e(key, action);
				callback(e);
			});

		glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos)
			{
				DATA data = *(DATA*)glfwGetWindowUserPointer(window);
				std::function<void(Event&)> callback = data.eventCallback;

				MouseMoveEvent e(xpos, ypos);
				callback(e);
				//glfwSetCursorPos(window, xpos, ypos);
			});

		glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods)
			{
				DATA data = *(DATA*)glfwGetWindowUserPointer(window);
				std::function<void(Event&)> callback = data.eventCallback;

				MouseOnClickEvent e(button, action);
				callback(e);
			});

		glfwSetWindowCloseCallback(window, [](GLFWwindow* window)
			{
				DATA data = *(DATA*)glfwGetWindowUserPointer(window);
				std::function<void(Event&)> callback = data.eventCallback;

				WindowCloseEvent e;
				callback(e);

			});

		glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height)
			{
				glViewport(0, 0, width, height);
				DATA* Data = (DATA*)glfwGetWindowUserPointer(window);
				Data->SCR_WIDTH = width;
				Data->SCR_HEIGHT = height;
				DATA data = *Data;
				std::function<void(Event&)> callback = data.eventCallback;

				WindowResizeEvent e(width, height);
				callback(e);
			});
	}

	void Window::end()
	{
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	void Window::ShutDown()
	{
		glfwTerminate();
	}

}