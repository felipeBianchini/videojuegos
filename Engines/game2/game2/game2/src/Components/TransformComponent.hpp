#ifndef TRANSFORMCOMPONENT_HPP
#define TRANSFORMCOMPONENT_HPP

#include <glm/glm.hpp>

struct TransformComponent {
	glm::vec2 position;
	glm::vec2 scale;
	glm::vec2 previousPosition;
	double rotation;

	TransformComponent(glm::vec2 position = glm::vec2(0.0, 0.0),
		glm::vec2 scale = glm::vec2(1.0, 1.0), double rotation = 0.0) {
		this->position = position;
		this->previousPosition = position;
		this->rotation = rotation;
		this->scale = scale;
	}
};

#endif // !TRANSFORMCOMPONENT_HPP
