/**
 * @file DamageSystem.hpp
 * @brief Defines the DamageSystem class for handling damage-related collision events
 */

#ifndef DAMAGESYSTEM_HPP
#define DAMAGESYSTEM_HPP
#include <memory>
#include <iostream>
#include "../ECS/ECS.hpp"
#include "../Components/CircleColliderComponent.hpp"
#include "../EventManager/EventManager.hpp"
#include "../Events/CollisionEvent.hpp"

/**
 * @class DamageSystem
 * @brief System responsible for handling damage when entities collide
 * 
 * This system processes entities with CircleColliderComponent and responds to
 * collision events by destroying the colliding entities.
 */
class DamageSystem : public System {
public:
    /**
     * @brief Constructor for DamageSystem
     * 
     * Sets up the required components for this system: CircleColliderComponent
     */
    DamageSystem() {
        RequiredComponent<CircleColliderComponent>();
    }

    /**
     * @brief Subscribes this system to collision events
     * 
     * Registers the OnCollision method as a callback for CollisionEvent,
     * allowing the system to respond when collisions occur.
     * 
     * @param eventManager Unique pointer to the event manager for subscribing to events
     */
    void SubscribeToCollisionEvent(std::unique_ptr<EventManager>& eventManager) {
        eventManager->SubscribeToEvent<CollisionEvent, DamageSystem>(this, &DamageSystem::OnCollision);
    }

    /**
     * @brief Handles collision events between entities
     * 
     * Called when a collision event is triggered. Destroys both entities
     * involved in the collision by calling their Kill() methods.
     * 
     * @param e Reference to the collision event containing the two colliding entities
     */
    void OnCollision(CollisionEvent& e) {
        e.a.Kill();
        e.b.Kill();
    }
};

#endif // !DAMAGESYSTEM_HPP