#pragma once
#include "bezel/Precompiled.h"
#include "bezel/include/Core.h"

// TODO: Create bus system for Event objects to avoid blocking (hanging up the sessions to process an event)
// The bus will create a queue of events that are executed when it is possible for the Event system

namespace Bezel {

	/*
		Event typer definert av relevante instanser.
	*/
	enum class EventType {
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped
	};

	/*
		Definert event kategorier for filtrering av kategorier gitt tillatelse basert på instans
	*/
	#pragma warning(push)	// Removes a warning that is a best practices suggestion which doesn't work on this project.
	#pragma warning(disable : 26812)
	enum EventCategory
	{
		None = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryInput = BIT(1),
		EventCategoryKeyboard = BIT(2),
		EventCategoryMouse = BIT(3),
		EventCategoryMouseButton = BIT(4)
	};
	#pragma warning(pop)
	/*
		Event type og kategori makro funksjonsdefinisjon
	*/
	#define EVENT_CLASS_TYPE(type) static EventType getStaticType() { return EventType::type; }\
		virtual EventType getEventType() const override { return getStaticType(); }\
		virtual const char* getName() const override { return #type; }
	#define EVENT_CLASS_CATEGORY(category) virtual int getCategoryFlags() const override { return category; }

	/*
		Event superclass for handling common functionality between events
	*/
	class EXPORTED Event {
		friend class EventDispatcher;
	protected:
		// Checks if event has been handled before or after runtime
		// aswell as blocking events further down the layer stack from executing after allocation to a suitable layer.
		bool m_Handled = false;
	public:
		bool handled = false;

		virtual const char* getName() const = 0;
		virtual int getCategoryFlags() const = 0;
		virtual EventType getEventType() const = 0;
		virtual std::string toString() const { return getName(); }

		inline bool isInCategory(EventCategory category) { return getCategoryFlags() &category; }
	};
	
	/*
		The EventDispatcher class handles dispatching events of any 'Event' subclass for ease of use.
	*/
	class EventDispatcher {
		template<typename T>
		using EventFn = std::function<bool(T&)>;
	private:
		Event& m_Event;
	public:
		EventDispatcher(Event& event) : m_Event(event) {}	// Receive any type of event as a reference

		// Check if current event matches specified filter and dispatch if match.
		template<typename T>
		bool Dispatch(EventFn<T> func) {
			if (m_Event.getEventType() == T::getStaticType()) {
				m_Event.m_Handled = func(*(T*)&m_Event);
				m_Event.handled = func(*(T*)&m_Event);
				return true;
			}
			else {
				return false;
			}
		}
	};

	/*
		Output stream operator for easier logging of events by string.
	*/
	inline std::ostream& operator << (std::ostream& os, const Event& e) {
		return os << e.toString();
	}
}

