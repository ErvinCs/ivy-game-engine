#pragma once

#include "../Core/String.h"
#include "../Core/Logger.h"
#include "../Exceptions/EventException.h"
#include <memory>
#include <vector>
#include <functional>
//#include <iostream>

namespace Ivy {

	class EventHandler {
	public:
		//TODO - add params
		using Func = std::function<void()>;

	private:
		Func callback;

	public:
		int id;
		static int counter;

		EventHandler() : id{ 0 } {
		}

		EventHandler(const Func &func) : callback{ func } {
			this->id = ++EventHandler::counter;
			IVY_CORE_TRACE("EventHandlerCounter (id) = {0}", EventHandler::counter);	
		}

		void operator()();
		void operator=(const EventHandler &func);
		bool operator==(const EventHandler &del);
		bool operator!=(nullptr_t);
	};


	class Event {
		std::vector<std::unique_ptr<EventHandler>> handlers;

		void notifyHandlers();
	public:
		void addHandler(const EventHandler &handler);
		void removeHandler(const EventHandler &handler);
		void operator()();
		Event &operator+=(const EventHandler &handler);
		Event &operator+=(const EventHandler::Func &handler);
		Event &operator-=(const EventHandler &handler);
		int totalHandlers() { return this->handlers.size(); }
	};
}