#pragma once
#include <functional>

namespace Dark
{

	enum class EventTypes
	{
		None = 0, MouseOnClick = 1, MouseMove = 2, MouseScroll = 3,
		KeyInput = 4,
		WindowClose = 5, WindowResize = 6
	};

#define EVENT_FUNCTIONS(type) virtual EventTypes getEventType() override { return EventTypes::##type; }\
							  static EventTypes getStaticEventType() { return EventTypes::##type; }\
							  virtual const char* getName() override { return #type; }


	class Event
	{
	public:
		virtual EventTypes getEventType() = 0;
		virtual const char* getName() = 0;

		static bool CheckEvent(EventTypes type, Event& e);
		template <typename T>
		static void CheckEventFunc(Event& e, std::function<void(T&)> func) 
		{
			if (T::getStaticEventType() == e.getEventType() && !e.m_handled)
			{
				T* event = static_cast<T*>(&e);
				func(*event);
			}
		};

		bool m_handled = false;
	};

	class MouseOnClickEvent : public Event
	{
	public:
		MouseOnClickEvent(int button, int action)
		{
			this->button = button;
			this->action = action;
		}

		int button, action;

		EVENT_FUNCTIONS(MouseOnClick)
	};

	class MouseMoveEvent : public Event
	{
	public:
		MouseMoveEvent(double x, double y)
		{
			posx = x;
			posy = y;
		}

		double posx, posy;

		EVENT_FUNCTIONS(MouseMove)
	};

	class MouseScrollEvent : public Event
	{
	public:
		MouseScrollEvent(double x, double y)
		{
			scrollx = x;
			scrolly = y;
		}

		double scrollx, scrolly;

		EVENT_FUNCTIONS(MouseScroll)
	};

	class KeyInputEvent : public Event
	{
	public:
		KeyInputEvent(int key, int action)
		{
			this->key = key;
			this->action = action;
		}

		int key, action;

		EVENT_FUNCTIONS(KeyInput)
	};

	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() {}

		EVENT_FUNCTIONS(WindowClose)
	};

	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(int width, int height)
		{
			this->width = width;
			this->height = height;
		}

		int width, height;

		EVENT_FUNCTIONS(WindowResize)
	};

}