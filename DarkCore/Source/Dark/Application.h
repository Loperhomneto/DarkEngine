#pragma once
#include <memory>
#include "Event.h"
#include "Window.h"
#include "LayerManager.h"
#include "Layer.h"

namespace Dark {

	class  Application
	{
	public:
		Application();
		virtual ~Application() = default;
		
		void pushLayer(std::shared_ptr<Layer>& layer);
		void pushLayerEnd(std::shared_ptr<Layer>& layer);
		void popLayer(std::shared_ptr<Layer>& layer);

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

		//TODO: make LayerManager shared_ptr
		std::shared_ptr<Window> m_window;
		LayerManager m_LayerManager;
	};

	Application* CreateApplication();
}

