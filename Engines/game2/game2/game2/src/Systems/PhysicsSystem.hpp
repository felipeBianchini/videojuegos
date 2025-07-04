/**
 * @file PhysicsSystem.hpp
 * @brief Physics system for handling rigid body dynamics
 */

#ifndef PHYSICSYSTEM_HPP
#define PHYSICSYSTEM_HPP
#include "../Components/RigidBodyComponent.hpp"
#include "../ECS/ECS.hpp"

/**
 * @class PhysicsSystem
 * @brief System responsible for updating physics calculations on entities with rigid bodies
 * 
 * This system processes all entities that have a RigidBodyComponent and applies
 * physics calculations such as gravity forces to dynamic rigid bodies.
 */
class PhysicsSystem : public System {
public:
    /**
     * @brief Constructor for PhysicsSystem
     * 
     * Initializes the physics system and sets up the required component type.
     * Only entities with RigidBodyComponent will be processed by this system.
     */
    PhysicsSystem() {
        RequiredComponent<RigidBodyComponent>();
    }
    
    /**
     * @brief Updates physics calculations for all entities in the system
     * 
     * Iterates through all entities with RigidBodyComponent and applies physics
     * forces. For dynamic rigid bodies, applies gravitational force based on
     * mass and gravity constant.
     */
    void Update() {
        for (auto entity : GetSystemEntiities()) {
            auto& rigidbody = entity.GetComponent<RigidBodyComponent>();
            if (rigidbody.isDynamic) {
                // Apply gravity force: F = m * g * scale_factor
                rigidbody.sumForces += glm::vec2(0.0f, 9.8 * rigidbody.mass * 64);
            }
        }
    }
};
#endif // !PHYSICSYSTEM_HPP