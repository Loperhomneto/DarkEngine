#pragma once
#include "Core.h"
#include <iostream>

namespace Dark
{

	class App : public Application
	{
	public:
		App();
	};

	class FooLayer : public Layer
	{
	public:
		virtual void OnEvent(Event& e) override;
		void EventWindowResize(WindowResizeEvent& e);
	};

}