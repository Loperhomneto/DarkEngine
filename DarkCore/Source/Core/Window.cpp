#include "Window.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <iostream>

namespace Dark
{

	Window::Window(int FPS, std::function<void(Event&)> func, std::string name)
	{
		fps = FPS;

		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, name.c_str(), NULL, NULL);

		if (window == NULL)
		{
			std::cout << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
		}
		glfwMakeContextCurrent(window);
		//glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
		}

		SetEventBindFuncs(func);
	}

	void Window::SetEventBindFuncs(std::function<void(Event&)> func)
	{
		eventCallback = func;

		glfwSetWindowUserPointer(window, &eventCallback);

		glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				std::function<void(Event&)> callback = *(std::function<void(Event&)>*)glfwGetWindowUserPointer(window);

				KeyInputEvent e(key, action);
				callback(e);
			});

		//glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos)
		//	{
		//		std::function<void(Event&)> callback = *(std::function<void(Event&)>*)glfwGetWindowUserPointer(window);

		//		MouseMoveEvent e(xpos, ypos);
		//		callback(e);
		//		glfwSetCursorPos(window, xpos, ypos);
		//	});

		glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods)
			{
				std::function<void(Event&)> callback = *(std::function<void(Event&)>*)glfwGetWindowUserPointer(window);

				MouseOnClickEvent e(button, action);
				callback(e);
			});

		glfwSetWindowCloseCallback(window, [](GLFWwindow* window)
			{
				std::function<void(Event&)> callback = *(std::function<void(Event&)>*)glfwGetWindowUserPointer(window);

				WindowCloseEvent e;
				callback(e);

			});

		glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height)
			{
				std::function<void(Event&)> callback = *(std::function<void(Event&)>*)glfwGetWindowUserPointer(window);

				WindowResizeEvent e(width, height);
				callback(e);
			});
	}

	void Window::OnUpdate()
	{
		double frametime = 1 / fps;
		timenext = glfwGetTime();
		if (timenext - timeprev > frametime)
		{
			timeprev = timenext;
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	}

	void Window::ShutDown()
	{
		glfwTerminate();
	}


}