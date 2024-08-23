#include "EventSystem.h"

void EventSystem::AddObserver(const id_t id, Observer* observer, EventHandler eventHandler) {
	Dispatcher dispatcher;
	dispatcher.observer = observer;
	dispatcher.eventHandler = eventHandler;

	m_dispatchers[id].push_back(dispatcher);
}

void EventSystem::RemoveObserver(Observer* observer) {
	for (auto& element : m_dispatchers) {
		auto disps = element.second;
		std::erase_if(disps, [observer](auto& disp) {return disp.observer == observer; });
	}
}

void EventSystem::Notify(const Event& event) {
	auto iter = m_dispatchers.find(event.id);
	if (iter != m_dispatchers.end()) {
		auto dispatchers = iter->second;
		for (auto& disp : dispatchers) {
			disp.eventHandler(event);
		}
	}
}