#ifndef COLLISIONEVENT_HPP
#define COLLISIONEVENT_HPP

#include "../EventManager/Event.hpp"
#include "../ECS/ECS.hpp"

/**
 * @class CollisionEvent
 * @brief Event triggered when two entities collide.
 *
 * This event is dispatched when a collision is detected between two entities
 * within the ECS framework. It provides references to both entities involved.
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
     * @brief Constructs a CollisionEvent with two colliding entities.
     *
     * @param a The first entity involved in the collision.
     * @param b The second entity involved in the collision.
     */
    CollisionEvent(Entity a, Entity b) : a(a), b(b) {}
};

#endif // !COLLISIONEVENT_HPP
