/**
 * @file BoxCollisionSystem.hpp
 * @brief System for detecting and handling box collider collisions
 */

#ifndef BOXCOLLISIONSYSTEM_HPP
#define BOXCOLLISIONSYSTEM_HPP
#include <memory>
#include "../Components/BoxColliderComponent.hpp"
#include "../Components/ScriptComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../EventManager/EventManager.hpp"
#include "../Events/CollisionEvent.hpp"
#include "../ECS/ECS.hpp"

/**
 * @class BoxCollisionSystem
 * @brief System responsible for detecting collisions between box colliders
 * 
 * This system performs collision detection between all entities that have both
 * BoxColliderComponent and TransformComponent. When collisions are detected,
 * it emits collision events and triggers script callbacks if entities have
 * ScriptComponent with collision handlers.
 */
class BoxCollisionSystem : public System {
private:
    /**
     * @brief Checks if two axis-aligned bounding boxes are colliding
     * 
     * Uses the separating axis theorem to determine if two rectangles overlap.
     * Returns true if the rectangles intersect, false otherwise.
     * 
     * @param aX X position of first rectangle
     * @param aY Y position of first rectangle
     * @param aW Width of first rectangle
     * @param aH Height of first rectangle
     * @param bX X position of second rectangle
     * @param bY Y position of second rectangle
     * @param bW Width of second rectangle
     * @param bH Height of second rectangle
     * @return true if rectangles are colliding, false otherwise
     */
    bool CheckCollision(float aX, float aY, float aW, float aH, float bX, float bY, float bW, float bH) {
        return(
            aX < bX + bW &&
            aX + aW > bX &&
            aY < bY + bH &&
            aY + aH > bY
        );
    }
    
public:
    /**
     * @brief Constructor for BoxCollisionSystem
     * 
     * Initializes the collision system and sets up the required component types.
     * Only entities with both BoxColliderComponent and TransformComponent will
     * be processed by this system.
     */
    BoxCollisionSystem() {
        RequiredComponent<BoxColliderComponent>();
        RequiredComponent<TransformComponent>();
    }
    
    /**
     * @brief Updates collision detection for all entities in the system
     * 
     * Performs pairwise collision detection between all entities with the required
     * components. When collisions are detected, emits CollisionEvent and triggers
     * script callbacks for entities that have ScriptComponent with onCollision handlers.
     * 
     * @param lua Lua state used for script execution
     * @param eventManager Event manager for emitting collision events
     */
    void Update(sol::state& lua, const std::unique_ptr<EventManager>& eventManager) {
        auto entities = GetSystemEntiities();
        
        // Check collisions between all pairs of entities
        for (auto i = entities.begin(); i != entities.end(); i++) {
            Entity a = *i;
            const auto& aCollider = a.GetComponent<BoxColliderComponent>();
            const auto& aTranform = a.GetComponent<TransformComponent>();
            
            for (auto j = i; j != entities.end(); j++) {
                Entity b = *j;
                if (a == b) {
                    continue;
                }
                
                const auto& bCollider = b.GetComponent<BoxColliderComponent>();
                const auto& bTranform = b.GetComponent<TransformComponent>();
                
                // Check if entities are colliding
                bool collision = CheckCollision(
                    aTranform.position.x, aTranform.position.y, static_cast<float>(aCollider.width), static_cast<float>(aCollider.heigth),
                    bTranform.position.x, bTranform.position.y, static_cast<float>(bCollider.width), static_cast<float>(bCollider.heigth)
                );
                
                if (collision) {
                    // Emit collision event
                    eventManager->EmitEvent<CollisionEvent>(a, b);
                    
                    // Trigger script callback for entity A
                    if (a.HasComponent<ScriptComponent>()) {
                        const auto& script = a.GetComponent<ScriptComponent>();
                        if (script.onCollision != sol::nil) {
                            lua["this"] = a;
                            script.onCollision(b);
                        }
                    }
                    
                    // Trigger script callback for entity B
                    if (b.HasComponent<ScriptComponent>()) {
                        const auto& script = b.GetComponent<ScriptComponent>();
                        if (script.onCollision != sol::nil) {
                            lua["this"] = b;
                            script.onCollision(a);
                        }
                    }
                }
            }
        }
    }
};
#endif // !BOXCOLLISIONSYSTEM_HPP