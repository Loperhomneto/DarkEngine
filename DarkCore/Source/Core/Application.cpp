#include "Application.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include <functional>


//std::bind(&Application::OnEvent, this, std::placeholders::_1)

namespace Dark {

#define DARK_BIND_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application::Application()
	{
		m_window = std::unique_ptr<Window>(new Window(fps, DARK_BIND_FN(OnEvent), "New Window"));
	}

	void Application::Run()
	{


		double timenext = 0.0;
		double timeprev = 0.0;
		double frametime = 1 / fps;
		while (m_running) 
		{
			m_window->OnUpdate();

			auto it = m_LayerManager.begin();
			for (s_Layer layer = m_LayerManager(it); it < m_LayerManager.end(); it++)
			{
				layer->OnUpdate();
			}
		}

	}

	void Application::OnEvent(Event& e)
	{
		Event::CheckEventFunc<MouseOnClickEvent>(e, DARK_BIND_FN(OnMouseClick));
		Event::CheckEventFunc<WindowCloseEvent>(e, DARK_BIND_FN(OnWindowClose));

		auto it = m_LayerManager.begin();
		for (s_Layer layer = m_LayerManager(it); it < m_LayerManager.end(); it++)
		{
			layer->OnEvent(e);
		}
	}

	void Application::OnMouseClick(MouseOnClickEvent& e)
	{
		if (e.button == 1)
		{
			std::cout << "Right Mouse Button ";
		}
		if (e.button == 0)
		{
			std::cout << "Left Mouse Button ";
		}
		if (e.action == 1)
		{
			std::cout << " Pressed" << std::endl;
		}
		if (e.action == 0)
		{
			std::cout << " Release " << std::endl;
		}
	}

	void Application::OnWindowClose(WindowCloseEvent& e)
	{
		Shutdown();
	}

	void Application::pushLayer(s_Layer& layer)
	{
		m_LayerManager.pushLayer(layer);
	}

	void Application::pushLayerEnd(s_Layer& layer)
	{
		m_LayerManager.pushLayerEnd(layer);
	}

	void Application::popLayer(s_Layer& layer)
	{
		m_LayerManager.popLayer(layer);
	}

	void Application::Shutdown()
	{
		m_window->ShutDown();
		m_running = false;
	}

}