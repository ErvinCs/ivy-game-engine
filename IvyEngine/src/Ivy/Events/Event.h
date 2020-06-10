#pragma once

#include <memory>
#include <vector>
#include <functional>
#include <sstream>

#include "../Core/Logger.h"
#include "../Exceptions/EventException.h"

namespace Ivy {
	
	class Event;

	/**
	 *
	 */
	class EventHandler {
	public:
		using Func = std::function<void(Event& e)>;

	public:
		// Defines the callback function
		Func callback;
		//
		Event* event;

	public:
		// Id of the handler
		int id;
		// Used to generate handler ids
		static int counter;

		// Default constructor. Creates an EventHandler with id 0.
		EventHandler() : id{ 0 } {
		}

		/**
		 *
		 */
		EventHandler(const Func &func) : callback{ func } {
			this->id = ++EventHandler::counter;
		}

		/**
		 * @returns Event* pointer to the event associated to the handler
		 */
		Event* getEvent() {
			return event;
		}

		//
		void operator()(Event& e);
		//
		void operator=(const EventHandler &func);
		//
		bool operator==(const EventHandler &del);
		//
		bool operator!=(nullptr_t);
	};

	/**
	 *
	 */
	class Event {
		// The EventHandlers that will be called in response to this Event being raised
		std::vector<std::unique_ptr<EventHandler>> handlers;

		/**
		 *
		 */
		void notifyHandlers();
	public:
		//
		int type;

		/**
		 *
		 */
		void addHandler(const EventHandler &handler);

		/**
		 *
		 */
		void removeHandler(const EventHandler &handler);

		/**
		 *
		 */
		void operator()();

		/**
		 *
		 */
		Event &operator+=(const EventHandler &handler);

		/**
		 *
		 */
		Event &operator+=(const EventHandler::Func &handler);

		/**
		 *
		 */
		Event &operator-=(const EventHandler &handler);

		//
		int totalHandlers() { return this->handlers.size(); }

		//
		virtual std::string toString() const;
	};


}