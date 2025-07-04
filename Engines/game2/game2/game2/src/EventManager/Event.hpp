#ifndef EVENT_HPP
#define EVENT_HPP

/**
 * @brief Base class for all events in the event system.
 * 
 * This class serves as the foundation for all event types in the system.
 * It provides a common interface that all specific event types inherit from.
 */
class Event {
public:
    /**
     * @brief Default constructor for Event.
     */
    Event() = default;
};

#endif // !EVENT_HPP