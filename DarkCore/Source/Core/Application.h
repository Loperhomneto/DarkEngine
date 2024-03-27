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
		void OnMouseClick(MouseOnClickEvent& e);
		void OnWindowClose(WindowCloseEvent& e);

		void Run();
	private:
		void Shutdown();
	private:
		bool m_running = true;

		int fps = 120;

		const int SCR_WIDTH = 800;
		const int SCR_HEIGHT = 600;

		std::unique_ptr<Window> m_window;
		LayerManager m_LayerManager;
	};

	Application* CreateApplication();
}

