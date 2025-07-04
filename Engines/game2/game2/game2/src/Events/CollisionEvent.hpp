#ifndef COLLISIONEVENT_HPP
#define COLLISIONEVENT_HPP
#include "../EventManager/Event.hpp"
#include "../ECS/ECS.hpp"

/**
 * @brief An event class representing a collision between two entities.
 * 
 * This class encapsulates information about a collision event,
 * containing references to the two entities that collided.
 */
class CollisionEvent : public Event {
public:
    /**
     * @brief The first entity involved in the collision.
     */
    Entity a;
    
    /**
     * @brief The second entity involved in the collision.
     */
    Entity b;
    
    /**
     * @brief Constructs a CollisionEvent with the two colliding entities.
     * 
     * @param a The first entity involved in the collision.
     * @param b The second entity involved in the collision.
     */
    CollisionEvent(Entity a, Entity b) : a(a), b(b) {}
};
#endif // !COLLISIONEVENT_HPP