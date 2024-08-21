#pragma once
#include "Event.h"
#include "Observer.h"
#include "Core/Singleton.h"

#include <functional>
#include <map>

#define SUBSCRIBE_OBSERVER(id, function)	EventSystem::Instance().AddObserver(#id, this, std::bind(&function, this, std::placeholders::_1));
#define EVENT_NOTIFY_DATA(id, data)			EventSystem::Instance().Notify({ #id, data });
#define EVENT_NOTIFY(id)					EventSystem::Instance().Notify({ #id, true });

class EventSystem : public Singleton<EventSystem> {
public:
	using EventHandler = std::function<void(const Event&)>;

	struct Dispatcher {
		Observer* observer{ nullptr };
		EventHandler eventHandler;
	};
public:
	void AddObserver(const id_t id, Observer* observer, EventHandler eventHandler);
	void Notify(const Event& event);
private:
	std::map<id_t, std::list<Dispatcher>> m_dispatchers;
};