#include "ivypch.h"
#include "Event.h"

namespace Ivy {

	using std::vector;
	using std::unique_ptr;

	int EventHandler::counter;

	void EventHandler::operator()() {
		this->callback();
	}

	void EventHandler::operator=(const EventHandler &func) {
		if (this->callback == nullptr) {
			this->callback = func;
			this->id = ++EventHandler::counter;
		}
		else {
			throw new EventException("Assignment failed: invalid EventHandler function!");
		}
	}

	bool EventHandler::operator==(const EventHandler &del) {
		return this->id == del.id;
	}
	bool EventHandler::operator!=(nullptr_t) {
		return this->callback != nullptr;
	}


	void Event::notifyHandlers() {
		vector<unique_ptr<EventHandler>>::iterator func = this->handlers.begin();
		for (; func != this->handlers.end(); ++func) {
			if (*func != nullptr && (*func)->id != 0) {
				(*(*func))();
				IVY_CORE_TRACE("EventHandler.id: {0}", (*func)->id);
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
				IVY_CORE_TRACE("Removing: {0}",  (*to_remove)->id);
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


}