#include "Application.h"
#include "Renderer.h"
#include "Input.h"
#include "TimeStep.h"
#include <iostream>
#include <functional>


//std::bind(&Application::OnEvent, this, std::placeholders::_1)

namespace Dark {

#define DARK_BIND_FN(x) std::bind(&Application::x, this, std::placeholders::_1)


	Application::Application()
	{
		m_window = std::unique_ptr<Window>(new Window(DARK_BIND_FN(OnEvent), "New Window", 800, 600));
		Renderer::Init();
	}

	void Application::Run()
	{
		while (m_running) 
		{
			timenext = Input::getProgramTime();
			double deltatime = timenext - timeprev;
			timeprev = timenext;
			TimeStep ts(deltatime);

			Renderer::startRendererCall(m_window->getScreenWidth(), m_window->getScreenHeight());

			auto it = m_LayerManager.begin();
			for (s_Layer layer = m_LayerManager(it); it < m_LayerManager.end(); it++)
			{
				layer->OnUpdate(ts);
			}
			m_window->end();
		}
	}

	void Application::OnEvent(Event& e)
	{
		Event::CheckEventFunc<WindowCloseEvent>(e, DARK_BIND_FN(OnWindowClose));

		auto it = m_LayerManager.begin();
		for (s_Layer layer = m_LayerManager(it); it < m_LayerManager.end(); it++)
		{
			layer->OnEvent(e);
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