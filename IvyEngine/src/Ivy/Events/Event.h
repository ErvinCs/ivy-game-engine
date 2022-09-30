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
	 * Maintains a pointer to a function that should be called in response to an Event.
	 * A pointer to the Event is maintained as well as the function object to be called.
	 * @see Event
	 */
	class EventHandler {
	public:
		using Func = std::function<void(Event& e)>;

	public:
		// Defines the callback function
		Func callback;
		// The Event to be listening to
		Event* event = nullptr;

	public:
		// Id of the handler
		int id;
		// Used to generate handler ids
		static int counter;

		// Default constructor. Creates an EventHandler with id 0.
		EventHandler() : id{ 0 } { }

		/**
		 * Sets the `callback` function to `func` and increases the counter
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

		// Sets the Event argument of the `callback` to the passed Event `e`
		void operator()(Event& e);

		/**
		 * Sets the callbac function to the passed `func` and increases the `counter`.
		 * @param func EventHandler
		 */
		void operator=(const EventHandler &func);

		/** 
		 * @param del EventHandler to compare to
		 * @returns true if the id of `this` is equal to the id of `del` and false otherwise
		 */
		bool operator==(const EventHandler &del);

		/** 
		* @returns true if `this` EventHandler is not null and false otherwise
		*/
		bool operator!=(nullptr_t);
	};

	/**
	 * Represents an Event.
	 * An event has an associated collection of handlers that are executed immediatly after the Event is raised.
	 * @see EventHandler
	 */
	class Event {
		// The EventHandlers that will be called in response to `this` Event being raised
		std::vector<std::unique_ptr<EventHandler>> handlers;

		/**
		 * Executes the `EventHandler`s associated with this Event
		 */
		void notifyHandlers();
	public:
		/**
		 * Represents the type of the Event.
		 * @see KeyEvent
		 * @see MouseEvent
		 * @see WindowEvent
		 */ 
		int type;

		/**
		 * Adds an EventHandler to the collection of handlers of this Event.
		 * @param handler EventHandler
		 */
		void addHandler(const EventHandler &handler);

		/**
		 * Removes an EventHandler from the collection of handlers of this Event.
		 * @param handler EventHandler
		 */
		void removeHandler(const EventHandler &handler);

		/**
		 * Calls `notifyHandlers` for this event.
		 */
		void operator()();

		/**
		 * @see addHandler
		 */
		Event &operator+=(const EventHandler &handler);

		/**
		 * @see addHandler
		 */
		Event &operator+=(const EventHandler::Func &handler);

		/**
		 * @see removeHandler
		 */
		Event &operator-=(const EventHandler &handler);

		// @returns int the number of handlers associated to this Event
		int totalHandlers() { return this->handlers.size(); }

		// @returns string describing this raised Event
		virtual std::string toString() const;
	};
}