#pragma once

#include <memory>
#include <vector>
#include <functional>
#include <sstream>

#include "../Core/Logger.h"
#include "../Exceptions/EventException.h"

namespace Ivy {
	
	class Event;

	class EventHandler {
	public:
		using Func = std::function<void(Event& e)>;

	public:
		Func callback;
		Event* event;

	public:
		int id;
		static int counter;

		EventHandler() : id{ 0 } {
		}

		EventHandler(const Func &func) : callback{ func } {
			this->id = ++EventHandler::counter;
			//IVY_CORE_TRACE("EventHandlerCounter (id) = {0}", EventHandler::counter);	
		}

		Event* getEvent() {
			return event;
		}

		void operator()(Event& e);
		void operator=(const EventHandler &func);
		bool operator==(const EventHandler &del);
		bool operator!=(nullptr_t);
	};

	class Event {
		std::vector<std::unique_ptr<EventHandler>> handlers;

		void notifyHandlers();
	public:
		//TODO
		int type;
		void addHandler(const EventHandler &handler);
		void removeHandler(const EventHandler &handler);
		void operator()();
		Event &operator+=(const EventHandler &handler);
		Event &operator+=(const EventHandler::Func &handler);
		Event &operator-=(const EventHandler &handler);
		int totalHandlers() { return this->handlers.size(); }

		virtual std::string toString() const;
	};


}