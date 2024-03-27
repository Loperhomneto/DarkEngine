#include "App.h"

namespace Dark
{
	App::App()
	{
		s_Layer layer = std::make_shared<FooLayer>();
		pushLayer(layer);
	}


	void FooLayer::OnEvent(Event& e)
	{
		std::cout << "EventName: ";
		std::cout << e.getName();

		if (Event::CheckEvent(EventTypes::MouseScroll, e))
		{
			std::cout << "Event Called";
		}

		Event::CheckEventFunc<WindowResizeEvent>(e, std::bind(&FooLayer::EventWindowResize, this, std::placeholders::_1));
		
		std::cout << std::endl;
	}

	void FooLayer::EventWindowResize(WindowResizeEvent& e)
	{
		std::cout << "Height: " << e.height << " Width: " << e.width;
	}

}



Dark::Application* Dark::CreateApplication()
{
	return new App();
}