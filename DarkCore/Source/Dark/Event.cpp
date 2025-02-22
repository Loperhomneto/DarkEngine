#pragma once
#include "dkpch.h"
#include "Event.h"
#include "Dark/Core.h"

namespace Dark
{

	bool Event::CheckEvent(EventTypes type, Event& e)
	{
		if (type == e.getEventType() && !e.handled)
		{
			//e.m_handled = true;
			return true;
		}
		return false;
	}

}