/**
 * @file CircleCollisionSystem.hpp
 * @brief Defines the CircleCollisionSystem class for handling circular collision detection
 */

#ifndef CIRCLECOLLISIONSYSTEM_HPP
#define CIRCLECOLLISIONSYSTEM_HPP
#include <memory>
#include "../ECS/ECS.hpp"
#include "../Components/CircleColliderComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../EventManager/EventManager.hpp"
#include "../Events/CollisionEvent.hpp"

/**
 * @class CircleCollisionSystem
 * @brief System responsible for detecting collisions between entities with circular colliders
 * 
 * This system processes entities that have both CircleColliderComponent and TransformComponent,
 * checking for collisions between circular shapes and emitting collision events when detected.
 */
class CircleCollisionSystem : public System {
public:
    /**
     * @brief Constructor for CircleCollisionSystem
     * 
     * Sets up the required components for this system: CircleColliderComponent and TransformComponent
     */
    CircleCollisionSystem() {
        RequiredComponent<CircleColliderComponent>();
        RequiredComponent<TransformComponent>();
    }

    /**
     * @brief Updates the collision system and checks for collisions between entities
     * 
     * Iterates through all entities with required components, performs collision detection
     * between circular colliders, and emits collision events when collisions are detected.
     * 
     * @param eventManager Unique pointer to the event manager for emitting collision events
     */
    void Update(std::unique_ptr<EventManager>& eventManager) {
        auto entities = GetSystemEntiities();
        for (auto i = entities.begin(); i != entities.end(); i++) {
            Entity a = *i;
            auto aCollider = a.GetComponent<CircleColliderComponent>();
            auto aTranform = a.GetComponent<TransformComponent>();
            for (auto j = i; j != entities.end(); j++) {
                Entity b = *j;
                if (a == b) {
                    continue;
                }
                auto bCollider = b.GetComponent<CircleColliderComponent>();
                auto bTranform = b.GetComponent<TransformComponent>();
                
                // Calculate center positions accounting for scale
                glm::vec2 aCenterPos = glm::vec2(
                    aTranform.position.x - (aCollider.width / 2) * aTranform.scale.x,
                    aTranform.position.y - (aCollider.height / 2) * aTranform.scale.y
                );
                glm::vec2 bCenterPos = glm::vec2(
                    bTranform.position.x - (bCollider.width / 2) * bTranform.scale.x,
                    bTranform.position.y - (bCollider.height / 2) * bTranform.scale.y
                );
                
                // Calculate scaled radii
                int aRadius = aCollider.radius * aTranform.scale.x;
                int bRadius = bCollider.radius * bTranform.scale.x;
                
                bool collision = CheckCircularCollision(aRadius, bRadius, aCenterPos, bCenterPos);
                if (collision) {
                    eventManager->EmitEvent<CollisionEvent>(a, b);
                }
            }
        }
    }

    /**
     * @brief Checks if two circular colliders are colliding
     * 
     * Performs distance-based collision detection between two circles by comparing
     * the distance between their centers with the sum of their radii.
     * 
     * @param aRadius Radius of the first circle
     * @param bRadius Radius of the second circle
     * @param aPos Center position of the first circle
     * @param bPos Center position of the second circle
     * @return true if the circles are colliding, false otherwise
     */
    bool CheckCircularCollision(int aRadius, int bRadius, glm::vec2 aPos, glm::vec2 bPos) {
        glm::vec2 dif = aPos - bPos;
        double length = glm::sqrt((dif.x * dif.x) + (dif.y * dif.y));
        // Hay colisión si la suma de los radios es mayor a la distancia entre centros
        return (aRadius + bRadius) >= length;
    }
};

#endif // !CIRCLECOLLISIONSYSTEM_HPP