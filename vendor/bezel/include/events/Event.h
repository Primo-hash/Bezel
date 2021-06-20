#pragma once
#include "bezel/include/Core.h"

#include <string>
#include <functional>

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
		KeyPressed, KeyReleased
	};

	/*
		Definert event kategorier for filtering av kategorier gitt tillatelse basert på instans
	*/
	enum EventCategory
	{
		None = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryInput = BIT(1),
		EventCategoryKeyboard = BIT(2),
		EventCategoryMouse = BIT(3),
		EventCategoryMouseButton = BIT(4)
	};

	/*
		Event type og kategori makro funksjonsdefinisjon
	*/
	#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
		virtual EventType GetEventType() const override { return GetStaticType(); }\
		virtual const char* GetName() const override { return #type; }
	#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	/*
		Event superclass for handling common functionality between events
	*/
	class EXPORTED Event {
		friend class EventDispatcher;
	protected:
		bool m_Handled = false;	// Sjekk om Event er fullført etter eller under kjøretid
	public:
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual EventType GetEventType() const = 0;
		virtual std::string ToString() const { return GetName(); }

		inline bool IsInCategory(EventCategory category) { return GetCategoryFlags() &category; }
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
			if (m_Event.GetEventType() == T::GetStaticType()) {
				m_Event.m_Handled = func(*(T*)&m_Event);
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
		return os << e.ToString();
	}
}

