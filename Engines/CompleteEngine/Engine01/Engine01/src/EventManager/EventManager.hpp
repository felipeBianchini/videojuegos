#ifndef EVENTMANAGER_HPP
#define EVENTMANAGER_HPP

#include <functional>
#include <list>
#include <map>
#include <memory>
#include <typeindex>
#include <iostream>

#include "Event.hpp"

/**
 * @class IEventCallback
 * @brief Base interface for all event callbacks.
 *
 * Provides a polymorphic interface to execute event callback functions.
 */
class IEventCallback {
public:
	virtual ~IEventCallback() = default;
	/**
	 * @brief Executes the callback using the provided event.
	 * @param e Reference to the event.
	 */
	void Execute(Event& e) {
		Call(e);
	}
private:
	/**
	 * @brief Internal method to invoke the callback.
	 * @param e Reference to the event.
	 */
	virtual void Call(Event& e) = 0;
};

/**
 * @class EventCallback
 * @brief Concrete implementation of IEventCallback for member function callbacks.
 *
 * Stores a pointer to an owner instance and its member function to be executed
 * when the associated event is emitted.
 *
 * @tparam TOwner The class type of the callback owner.
 * @tparam TEvent The specific event type this callback handles.
 */
template <typename TOwner, typename TEvent>
class EventCallback : public IEventCallback {
private:
	typedef void (TOwner::*CallbackFunction)(TEvent&);

	TOwner* ownerInstance;                ///< Pointer to the callback owner instance.
	CallbackFunction callbackFunction;    ///< Pointer to the owner's member function.
	/**
	 * @brief Invokes the owner's callback function using the given event.
	 * @param e Reference to the base Event, cast to TEvent.
	 */
	virtual void Call(Event& e) override {
		std::invoke(callbackFunction, ownerInstance, static_cast<TEvent&>(e));
	}

public:
	/**
	 * @brief Constructs the callback.
	 * @param ownerInstance Pointer to the owner of the callback.
	 * @param callbackFunction Member function to be called when the event is emitted.
	 */
	EventCallback(TOwner* ownerInstance, CallbackFunction callbackFunction) {
		this->callbackFunction = callbackFunction;
		this->ownerInstance = ownerInstance;
	}
};
/**
 * @brief List of unique pointers to event callback handlers.
 */
typedef std::list<std::unique_ptr<IEventCallback>> HandlerList;

/**
 * @class EventManager
 * @brief Implements a publish-subscribe event handling system.
 *
 * Allows game systems or objects to subscribe to specific event types and
 * be notified when those events are emitted.
 */
class EventManager {
public:
	/**
	 * @brief Constructs the EventManager.
	 */
	EventManager() {
		std::cout << "[EventManager] se ejecuta constructor" << std::endl;
	}
	/**
	 * @brief Destroys the EventManager and clears all subscriptions.
	 */
	~EventManager() {
		std::cout << "[EventManager] se ejecuta destructor" << std::endl;
	}
	/**
	 * @brief Clears all event subscribers.
	 */
	void Reset() {
		subscribers.clear();
	}
	/**
	 * @brief Subscribes a method of an object to a specific event type.
	 *
	 * @tparam TEvent The event type to subscribe to.
	 * @tparam TOwner The type of the object subscribing to the event.
	 * @param ownerInstance Pointer to the subscriber instance.
	 * @param callbackFunction Pointer to the subscriber's callback method.
	 */
	template <typename TEvent, typename TOwner>
	void SubscribeToEvent(TOwner* ownerInstance, void (TOwner::*callbackFunction)(TEvent&)) {
		if (!subscribers[typeid(TEvent)].get()) {
			subscribers[typeid(TEvent)] = std::make_unique<HandlerList>();
		}
		auto subscriber = std::make_unique<EventCallback<TOwner, TEvent>>(ownerInstance, callbackFunction);
		subscribers[typeid(TEvent)]->push_back(std::move(subscriber));
	}
	/**
	 * @brief Emits an event of type TEvent and notifies all subscribers.
	 *
	 * @tparam TEvent The type of the event being emitted.
	 * @tparam TArgs Variadic arguments used to construct the event.
	 * @param args Arguments forwarded to the TEvent constructor.
	 */
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
	/**
	 * @brief Map of event type to its list of subscribed handlers.
	 */
	std::map<std::type_index, std::unique_ptr<HandlerList>> subscribers;

};

#endif // !EVENTMANAGER_HPP