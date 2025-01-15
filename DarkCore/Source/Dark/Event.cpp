#pragma once
#include "Event.h"
#include <functional>

namespace Dark
{

	bool Event::CheckEvent(EventTypes type, Event& e)
	{
		if (type == e.getEventType() && !e.m_handled)
		{
			//e.m_handled = true;
			return true;
		}
		return false;
	}

}