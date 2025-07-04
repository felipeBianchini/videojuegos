#ifndef TRANSFORMCOMPONENT_HPP
#define TRANSFORMCOMPONENT_HPP
#include <glm/glm.hpp>

/**
 * @brief A component that holds spatial transformation data for 2D objects.
 * 
 * This structure represents a transform component used for positioning,
 * scaling, and rotating entities in 2D space. It also tracks the previous
 * position for movement calculations or collision detection.
 */
struct TransformComponent {
    /**
     * @brief The current position of the entity in 2D space.
     */
    glm::vec2 position;
    
    /**
     * @brief The scale factor for the entity in both X and Y dimensions.
     */
    glm::vec2 scale;
    
    /**
     * @brief The previous position of the entity, used for movement tracking.
     */
    glm::vec2 previousPosition;
    
    /**
     * @brief The rotation angle of the entity in radians.
     */
    double rotation;
    
    /**
     * @brief Constructs a TransformComponent with specified position, scale, and rotation.
     * 
     * @param position The initial position of the entity. Defaults to (0.0, 0.0).
     * @param scale The initial scale of the entity. Defaults to (1.0, 1.0).
     * @param rotation The initial rotation angle in radians. Defaults to 0.0.
     */
    TransformComponent(glm::vec2 position = glm::vec2(0.0, 0.0),
                      glm::vec2 scale = glm::vec2(1.0, 1.0), double rotation = 0.0) {
        this->position = position;
        this->previousPosition = position;
        this->rotation = rotation;
        this->scale = scale;
    }
};
#endif // !TRANSFORMCOMPONENT_HPP