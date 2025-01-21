#pragma once
#include "Layer.h"

namespace Dark
{

	class ImGuiLayer : public Layer
	{
	public:
		virtual void OnAttach() override;
		virtual void OnDetach() override;

		virtual void OnUpdate(TimeStep ts);
		virtual void OnEvent(Event& e);
	};			

}
