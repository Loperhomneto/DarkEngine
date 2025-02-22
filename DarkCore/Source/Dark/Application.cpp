#include "dkpch.h"
#include "Dark/Core.h"
#include "Application.h"
#include "Renderer/Renderer.h"
#include "Input.h"
#include "TimeStep.h"


//std::bind(&Application::OnEvent, this, std::placeholders::_1)

namespace Dark {

#define DARK_BIND_FN(x) std::bind(&Application::x, this, std::placeholders::_1)


	Application::Application()
	{
		m_window = std::make_shared<Window>(DARK_BIND_FN(OnEvent), "New Window", 1280, 720);
		Renderer::Init(m_window, true);

#ifdef DK_DEBUG
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
	}
	
	void Application::Run()
	{
		while (m_running) 
		{
			timenext = Input::getProgramTime();
			double deltatime = timenext - timeprev;
			timeprev = timenext;
			TimeStep ts(deltatime);

			Renderer::startRendererCall();
			Renderer::OnUpdate(ts);

			auto it = m_LayerManager.begin();
			for (s_Layer layer = m_LayerManager(it); it < m_LayerManager.end(); it++)
			{
				layer->OnUpdate(ts);
			}

			Renderer::endRendererCall();

			unsigned int colorAttachmnetRendererID = Renderer::getColorAttachment();
			it = m_LayerManager.begin();
			for (s_Layer layer = m_LayerManager(it); it < m_LayerManager.end(); it++)
			{
				layer->ImGuiRender(colorAttachmnetRendererID);
			}

			Renderer::endImguiRendererCall();

			m_window->end();
			//_CrtDumpMemoryLeaks();
		}
	}

	void Application::OnEvent(Event& e)
	{
		Event::CheckEventFunc<WindowCloseEvent>(e, DARK_BIND_FN(OnWindowClose));
		Event::CheckEventFunc<WindowResizeEvent>(e, DARK_BIND_FN(OnWindowResize));

		auto it = m_LayerManager.begin();
		for (s_Layer layer = m_LayerManager(it); it < m_LayerManager.end(); it++)
		{
			if (!e.handled)
				layer->OnEvent(e);
		}

		if (!e.handled)
			Renderer::OnEvent(e);
	}

	void Application::OnWindowClose(WindowCloseEvent& e)
	{
		Shutdown();
	}

	void Application::OnWindowResize(WindowResizeEvent& e)
	{
		Renderer::OnWindowResize(e);
	}

	void Application::pushLayer(std::shared_ptr<Layer>& layer)
	{
		m_LayerManager.pushLayer(layer);
		layer->OnAttach();
	}

	void Application::pushLayerEnd(std::shared_ptr<Layer>& layer)
	{
		m_LayerManager.pushLayerEnd(layer);
		layer->OnAttach();
	}

	void Application::popLayer(std::shared_ptr<Layer>& layer)
	{
		m_LayerManager.popLayer(layer);
		layer->OnDetach();
	}

	void Application::Shutdown()
	{
		Renderer::Shutdown();
		m_window->ShutDown();
		m_running = false;
	}

}