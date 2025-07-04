/**
 * @file RigidBodyComponent.hpp
 * @brief Component for physics simulation of rigid body entities
 */

#ifndef RIGIDBODYCOMPONENT_HPP
#define RIGIDBODYCOMPONENT_HPP
#include <glm/glm.hpp>

/**
 * @struct RigidBodyComponent
 * @brief Component that provides physics properties and dynamics for entities
 * 
 * This component enables entities to participate in physics simulation by storing
 * physical properties like mass, velocity, and acceleration. It supports both
 * dynamic (movable) and static (immovable) bodies, with collision response
 * controlled by the isSolid flag.
 */
struct RigidBodyComponent {
    bool isDynamic;              ///< Whether the body can move and respond to forces
    bool isSolid;                ///< Whether the body participates in collision response
    float mass;                  ///< Mass of the body in physics units
    float invMass;               ///< Inverse mass (1/mass) for efficient physics calculations
    glm::vec2 velocity = glm::vec2(0);      ///< Current velocity vector in units per second
    glm::vec2 acceleration = glm::vec2(0);  ///< Current acceleration vector in units per second²
    glm::vec2 sumForces = glm::vec2(0);     ///< Accumulated forces applied to the body this frame
    
    /**
     * @brief Constructor for RigidBodyComponent
     * @param isDynamic Whether the body can move and respond to forces (default: false)
     * @param isSolid Whether the body participates in collision response (default: false)
     * @param mass Mass of the body in physics units (default: 1)
     * 
     * The constructor automatically calculates the inverse mass for efficient physics
     * computations. Static bodies (isDynamic = false) are typically used for
     * immovable objects like walls or platforms.
     */
    RigidBodyComponent(bool isDynamic = false, bool isSolid = false, float mass = 1) {
        this->isDynamic = isDynamic;
        this->mass = mass;
        this->invMass = 1 / mass;
        this->isSolid = isSolid;
    }
};

#endif // RIGIDBODYCOMPONENT_HPP