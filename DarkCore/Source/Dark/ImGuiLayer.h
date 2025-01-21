#pragma once
#include "Layer.h"

namespace Dark
{

	class ImGuiLayer : public Layer
	{
	public:
		virtual void OnAttach() override;
		void virtual OnUpdate(TimeStep ts) {};
		void virtual OnEvent(Event& e) {};
	};

}
