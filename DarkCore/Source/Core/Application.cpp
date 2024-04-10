#include "Application.h"
#include "Renderer.h"
#include "Input.h"
#include <iostream>
#include <functional>


//std::bind(&Application::OnEvent, this, std::placeholders::_1)

namespace Dark {

#define DARK_BIND_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application::Application()
	{
		m_window = std::unique_ptr<Window>(new Window(fps, DARK_BIND_FN(OnEvent), "New Window", 800, 600));
		Renderer::Init();
	}

	void Application::Run()
	{
		while (m_running) 
		{
			double frametime = (double)1/fps;
			timenext = Input::getTime();
			if (timenext - timeprev > frametime)
			{
				//std::cout << "Frametime: " << frametime;
				//std::cout << " Timenext: " << timenext;
				//std::cout << " TimePrev:" << timeprev << std::endl;
				timeprev = timenext;
				Renderer::startRendererCall(m_window->getScreenWidth(), m_window->getScreenHeight());

				auto it = m_LayerManager.begin();
				for (s_Layer layer = m_LayerManager(it); it < m_LayerManager.end(); it++)
				{
					layer->OnUpdate();
				}
				m_window->end();
			}
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

	//void Application::OnMouseClick(MouseOnClickEvent& e)
//{
//	if (e.button == 1)
//	{
//		std::cout << "Right Mouse Button ";
//	}
//	if (e.button == 0)
//	{
//		std::cout << "Left Mouse Button ";
//	}
//	if (e.action == 1)
//	{
//		std::cout << " Pressed" << std::endl;
//	}
//	if (e.action == 0)
//	{
//		std::cout << " Release " << std::endl;
//	}
//}
//}

}