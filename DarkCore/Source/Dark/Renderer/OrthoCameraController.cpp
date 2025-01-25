#include "dkpch.h"
#include "OrthoCameraController.h"
#include "Dark/KeyCodes.h"

namespace Dark
{

#define DARK_BIND_FN(x) std::bind(&OrthoCameraController::x, this, std::placeholders::_1)

	OrthoCameraController::OrthoCameraController()
	{
		
	}

	void OrthoCameraController::OnUpdate(TimeStep ts)
	{

	}

	void OrthoCameraController::OnEvent(Event& e)
	{
		Event::CheckEventFunc<WindowResizeEvent>(e, DARK_BIND_FN(OnWindowResize));
		Event::CheckEventFunc<MouseScrollEvent>(e, DARK_BIND_FN(OnMouseScroll));
	}

	void OrthoCameraController::OnWindowResize(WindowResizeEvent& e)	
	{
	}

	void OrthoCameraController::OnMouseScroll(MouseScrollEvent& e)
	{

	}

}