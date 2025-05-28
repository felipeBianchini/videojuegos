#ifndef TRANSFORMCOMPONENT_HPP
#define TRANSFORMCOMPONENT_HPP

#include <glm/glm.hpp>

/**
 * @brief Component that stores spatial transformation data for an entity.
 *
 * Includes position, scale, and rotation, commonly used for rendering and physics.
 */
struct TransformComponent {
	glm::vec2 position; ///< The position of the entity in world space.
	glm::vec2 scale;    ///< The scaling factor of the entity.
	double rotation;    ///< The rotation angle in degrees or radians (depending on usage context).

	/**
	 * @brief Constructs a TransformComponent with specified position, scale, and rotation.
	 *
	 * @param position The initial position of the entity. Defaults to (0,0).
	 * @param scale The initial scale of the entity. Defaults to (1,1).
	 * @param rotation The initial rotation of the entity. Defaults to 0.
	 */
	TransformComponent(glm::vec2 position = glm::vec2(0.0, 0.0),
		glm::vec2 scale = glm::vec2(1.0, 1.0), double rotation = 0.0) {
		this->position = position;
		this->rotation = rotation;
		this->scale = scale;
	}
};

#endif // !TRANSFORMCOMPONENT_HPP
