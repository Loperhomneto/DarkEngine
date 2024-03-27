#pragma once
#include "Event.h"

namespace Dark {

	class Layer
	{
	public:
		Layer() {};
		virtual ~Layer() {};

		void virtual OnUpdate() {};
		void virtual OnEvent(Event& e) {};
	};

}