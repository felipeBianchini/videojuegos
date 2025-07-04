/**
 * @file EventManager.hpp
 * @brief Event management system for handling type-safe event callbacks
 */

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
 * @brief Abstract base class for event callback handlers
 * 
 * Provides a common interface for all event callback implementations.
 * Uses the Template Method pattern to allow derived classes to implement
 * specific callback behavior.
 */
class IEventCallback {
public:
    /**
     * @brief Virtual destructor for proper cleanup of derived classes
     */
    virtual ~IEventCallback() = default;
    
    /**
     * @brief Executes the callback with the provided event
     * @param e Reference to the event to be processed
     */
    void Execute(Event& e) {
        Call(e);
    }
    
private:
    /**
     * @brief Pure virtual method to be implemented by derived classes
     * @param e Reference to the event to be processed
     */
    virtual void Call(Event& e) = 0;
};

/**
 * @class EventCallback
 * @brief Template class for type-safe event callbacks
 * @tparam TOwner The type of the object that owns the callback method
 * @tparam TEvent The type of event this callback handles
 * 
 * Implements the IEventCallback interface for specific owner and event types.
 * Stores a pointer to the owner instance and a member function pointer.
 */
template <typename TOwner, typename TEvent>
class EventCallback : public IEventCallback {
private:
    /**
     * @brief Type alias for the callback function pointer
     */
    typedef void (TOwner::*CallbackFunction)(TEvent&);
    
    /**
     * @brief Pointer to the instance that owns the callback method
     */
    TOwner* ownerInstance;
    
    /**
     * @brief Pointer to the member function to be called
     */
    CallbackFunction callbackFunction;
    
    /**
     * @brief Implementation of the pure virtual Call method
     * @param e Reference to the event to be processed
     * 
     * Casts the generic Event reference to the specific event type
     * and invokes the callback function on the owner instance.
     */
    virtual void Call(Event& e) override {
        std::invoke(callbackFunction, ownerInstance, static_cast<TEvent&>(e));
    }
    
public:
    /**
     * @brief Constructor for EventCallback
     * @param ownerInstance Pointer to the object that owns the callback method
     * @param callbackFunction Pointer to the member function to be called
     */
    EventCallback(TOwner* ownerInstance, CallbackFunction callbackFunction) {
        this->callbackFunction = callbackFunction;
        this->ownerInstance = ownerInstance;
    }
};

/**
 * @brief Type alias for a list of event callback handlers
 */
typedef std::list<std::unique_ptr<IEventCallback>> HandlerList;

/**
 * @class EventManager
 * @brief Central event management system
 * 
 * Manages event subscriptions and emissions. Provides type-safe event handling
 * by mapping event types to lists of callback handlers. Supports subscription
 * to events and emission of events with arbitrary arguments.
 */
class EventManager {
public:
    /**
     * @brief Constructor for EventManager
     * 
     * Initializes the event manager and outputs a debug message.
     */
    EventManager() {
        std::cout << "[EventManager] se ejecuta constructor" << std::endl;
    }
    
    /**
     * @brief Destructor for EventManager
     * 
     * Cleans up the event manager and outputs a debug message.
     */
    ~EventManager() {
        std::cout << "[EventManager] se ejecuta destructor" << std::endl;
    }
    
    /**
     * @brief Resets the event manager by clearing all subscriptions
     */
    void Reset() {
        subscribers.clear();
    }
    
    /**
     * @brief Subscribes an object method to a specific event type
     * @tparam TEvent The type of event to subscribe to
     * @tparam TOwner The type of the object that owns the callback method
     * @param ownerInstance Pointer to the object instance
     * @param callbackFunction Pointer to the member function to be called when the event occurs
     * 
     * Creates a new callback handler and adds it to the list of subscribers
     * for the specified event type. If no handler list exists for the event type,
     * a new one is created.
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
     * @brief Emits an event to all subscribed handlers
     * @tparam TEvent The type of event to emit
     * @tparam TArgs Variadic template for event constructor arguments
     * @param args Arguments to forward to the event constructor
     * 
     * Creates an instance of the specified event type and calls all registered
     * handlers for that event type. Uses perfect forwarding to pass arguments
     * to the event constructor.
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
     * @brief Map of event types to their corresponding handler lists
     * 
     * Uses std::type_index as the key to identify event types at runtime.
     * Each event type maps to a unique list of callback handlers.
     */
    std::map<std::type_index, std::unique_ptr<HandlerList>> subscribers;
};

#endif // !EVENTMANAGER_HPP