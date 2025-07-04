/**
 * @file MovementSystem.hpp
 * @brief Defines the MovementSystem class for handling entity movement and physics
 */

#ifndef MOVEMENTSYSTEM_HPP
#define MOVEMENTSYSTEM_HPP
#include <glm/glm.hpp>
#include "../Components/RigidBodyComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../ECS/ECS.hpp"

/**
 * @class MovementSystem
 * @brief System responsible for updating entity positions based on physics calculations
 * 
 * This system processes entities that have both RigidBodyComponent and TransformComponent,
 * handling movement with physics simulation for dynamic bodies and simple velocity-based
 * movement for static bodies.
 */
class MovementSystem : public System {
public:
    /**
     * @brief Constructor for MovementSystem
     * 
     * Sets up the required components for this system: RigidBodyComponent and TransformComponent
     */
    MovementSystem() {
        RequiredComponent<RigidBodyComponent>();
        RequiredComponent<TransformComponent>();
    }

    /**
     * @brief Updates all entities with movement calculations
     * 
     * Iterates through all entities with required components and updates their positions
     * based on their physics properties. For dynamic bodies, applies force-based physics
     * with acceleration and mass calculations. For static bodies, applies simple velocity-based movement.
     * 
     * @param dt Delta time in seconds since the last update
     */
    void Update(double dt) {
        for (auto entity : GetSystemEntiities()) {
            auto& rigidBody = entity.GetComponent<RigidBodyComponent>();
            auto& transform = entity.GetComponent<TransformComponent>();
            
            // Store previous position for collision detection or interpolation
            transform.previousPosition = transform.position;
            
            if (rigidBody.isDynamic) {
                // Physics-based movement with force, acceleration, and mass
                rigidBody.acceleration = rigidBody.sumForces * rigidBody.invMass;
                rigidBody.velocity += rigidBody.acceleration * static_cast<float>(dt);
                transform.position += rigidBody.velocity * static_cast<float>(dt);
                
                // Reset accumulated forces for next frame
                rigidBody.sumForces = glm::vec2(0);
            }
            else {
                // Simple velocity-based movement for static bodies
                transform.position.x += rigidBody.velocity.x * dt;
                transform.position.y += rigidBody.velocity.y * dt;
            }
        }
    }
};

#endif // MOVEMENTSYSTEM_HPP