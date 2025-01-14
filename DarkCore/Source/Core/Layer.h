#pragma once
#include "Event.h"
#include "TimeStep.h"
namespace Dark {

	class Layer
	{
	public:
		Layer() {};
		virtual ~Layer() {};

		void virtual OnUpdate(TimeStep ts) {};
		void virtual OnEvent(Event& e) {};
	};

}