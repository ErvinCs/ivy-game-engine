#include "ivypch.h"
#include "Event.h"

namespace Ivy {

	using std::vector;
	using std::unique_ptr;

	int EventHandler::counter;

	void EventHandler::operator()(Event& e) {
		this->callback(e);
	}

	void EventHandler::operator=(const EventHandler &func) {
		if (this->callback == nullptr) {
			this->callback = func;
			this->id = ++EventHandler::counter;
		}
		else {
			IVY_CORE_WARN("EventHandler: Throwing EventException: Failed Assignment");
			throw new EventException("EventHandler: Assignment failed: invalid EventHandler function!");
		}
	}

	bool EventHandler::operator==(const EventHandler &del) {
		return this->id == del.id;
	}

	bool EventHandler::operator!=(nullptr_t) {
		return this->callback != nullptr;
	}


	void Event::notifyHandlers() {
		IVY_CORE_TRACE("Event: Notifying Handlers.");
		vector<unique_ptr<EventHandler>>::iterator func = this->handlers.begin();
		for (; func != this->handlers.end(); ++func) {
			if (*func != nullptr && (*func)->id != 0) {
				Event* e = (*func)->getEvent();
				(*(*func))(*e);
				IVY_CORE_TRACE("Event: Calling EventHandler: handlerId={0}", (*func)->id);
			}
		}
	}

	void Event::addHandler(const EventHandler &handler) {
		this->handlers.push_back(unique_ptr<EventHandler>(new EventHandler{ handler }));
	}

	void Event::removeHandler(const EventHandler &handler) {
		vector<unique_ptr<EventHandler>>::iterator to_remove = this->handlers.begin();
		for (; to_remove != this->handlers.end(); ++to_remove) {
			if (*(*to_remove) == handler) {
				IVY_CORE_TRACE("Event: Removing Handler: handlerId={0}",  (*to_remove)->id);
				this->handlers.erase(to_remove);
				break;
			}
		}
	}

	void Event::operator()() {
		this->notifyHandlers();
	}

	Event &Event::operator+=(const EventHandler &handler) {
		this->addHandler(handler);

		return *this;
	}

	Event &Event::operator+=(const EventHandler::Func &handler) {
		this->addHandler(EventHandler{ handler });

		return *this;
	}

	Event &Event::operator-=(const EventHandler &handler) {
		this->removeHandler(handler);

		return *this;
	}

	std::string Event::toString() const {
		return "Event";
	}
}