#ifndef EVENT_HPP
#define EVENT_HPP

/**
 * @class Event
 * @brief Base class for all events in the event system.
 *
 * This is an abstract base class meant to be inherited by specific event types.
 * It allows the EventManager to handle all events in a generic way.
 */
class Event {
public:
    /**
     * @brief Default constructor.
     */
	Event() = default;
};



#endif // !EVENT_HPP
