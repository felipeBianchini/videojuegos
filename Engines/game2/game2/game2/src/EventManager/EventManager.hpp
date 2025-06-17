#ifndef EVENTMANAGER_HPP
#define EVENTMANAGER_HPP

#include <functional>
#include <list>
#include <map>
#include <memory>
#include <typeindex>
#include <iostream>

#include "Event.hpp"

class IEventCallback {
public:
	virtual ~IEventCallback() = default;
	void Execute(Event& e) {
		Call(e);
	}
private:
	virtual void Call(Event& e) = 0;
};

template <typename TOwner, typename TEvent>
class EventCallback : public IEventCallback {
private:
	typedef void (TOwner::*CallbackFunction)(TEvent&);

	TOwner* ownerInstance;
	CallbackFunction callbackFunction;

	virtual void Call(Event& e) override {
		std::invoke(callbackFunction, ownerInstance, static_cast<TEvent&>(e));
	}

public:
	EventCallback(TOwner* ownerInstance, CallbackFunction callbackFunction) {
		this->callbackFunction = callbackFunction;
		this->ownerInstance = ownerInstance;
	}
};

typedef std::list<std::unique_ptr<IEventCallback>> HandlerList;

class EventManager {
public:
	EventManager() {
		std::cout << "[EventManager] se ejecuta constructor" << std::endl;
	}
	~EventManager() {
		std::cout << "[EventManager] se ejecuta destructor" << std::endl;
	}
	void Reset() {
		subscribers.clear();
	}
	template <typename TEvent, typename TOwner>
	void SubscribeToEvent(TOwner* ownerInstance, void (TOwner::*callbackFunction)(TEvent&)) {
		if (!subscribers[typeid(TEvent)].get()) {
			subscribers[typeid(TEvent)] = std::make_unique<HandlerList>();
		}
		auto subscriber = std::make_unique<EventCallback<TOwner, TEvent>>(ownerInstance, callbackFunction);
		subscribers[typeid(TEvent)]->push_back(std::move(subscriber));
	}
	template <typename TEvent, typename... TArgs>
	void EmitEvent(TArgs&&... args) {
		auto handlers = subscribers[typeid(TEvent)].get();
		if (handlers) {
			for (auto it = handlers->begin(); it != handlers->end(); it++) {
				auto handler = it->get();
				TEvent event(std::forward<TArgs>(args)...);
				handler->Execute(event);
			}
		}
	}
private:
	std::map<std::type_index, std::unique_ptr<HandlerList>> subscribers;

};

#endif // !EVENTMANAGER_HPP