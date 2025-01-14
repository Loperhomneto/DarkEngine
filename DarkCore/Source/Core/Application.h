#pragma once
#include <memory>
#include "Event.h"
#include "Window.h"
#include "LayerManager.h"

namespace Dark {

	class  Application
	{
	public:
		Application();
		virtual ~Application() = default;
		
		void pushLayer(s_Layer& layer);
		void pushLayerEnd(s_Layer& layer);
		void popLayer(s_Layer& layer);

		void OnEvent(Event& e);
		void OnWindowClose(WindowCloseEvent& e);

		void Run();
	private:
		void Shutdown();
	private:
		bool m_running = true;

		double timenext = 0.0;
		double timeprev = 0.0;
		int capfps = 540;

		std::unique_ptr<Window> m_window;
		LayerManager m_LayerManager;
	};

	Application* CreateApplication();
}

