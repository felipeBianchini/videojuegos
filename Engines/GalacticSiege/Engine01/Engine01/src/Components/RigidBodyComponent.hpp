#ifndef RIGIDBODYCOMPONENT_HPP
#define RIGIDBODYCOMPONENT_HPP

#include <glm/glm.hpp>

/**
 * @brief Component that stores velocity for physics calculations.
 */
struct RigidBodyComponent {
	glm::vec2 velocity;  ///< Velocity vector of the entity.

    /**
     * @brief Construct a new Rigid Body Component object
     *
     * @param velocity Initial velocity (default is zero vector).
     */
	RigidBodyComponent(glm::vec2 velocity = glm::vec2(0.0)) {
		this->velocity = velocity;
	}
};

#endif // RIGIDBODYCOMPONENT_HPP