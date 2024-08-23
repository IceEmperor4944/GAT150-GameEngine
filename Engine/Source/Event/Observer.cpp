#include "Observer.h"
#include "EventSystem.h"

Observer::~Observer() {
	REMOVE_OBSERVER;
}