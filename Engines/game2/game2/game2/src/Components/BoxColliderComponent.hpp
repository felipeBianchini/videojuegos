/**
 * @file BoxColliderComponent.hpp
 * @brief Component for rectangular collision detection in the ECS system
 */

#ifndef BOXCOLLIDERCOMPONENT_HPP
#define BOXCOLLIDERCOMPONENT_HPP
#include <glm/glm.hpp>

/**
 * @struct BoxColliderComponent
 * @brief Component that defines a rectangular collision box for entities
 * 
 * This component provides rectangular collision detection capabilities by defining
 * a bounding box with customizable dimensions and offset from the entity's position.
 * It's used by the physics system to detect collisions between entities.
 */
struct BoxColliderComponent {
    int width;           ///< Width of the collision box in pixels
    int heigth;          ///< Height of the collision box in pixels
    glm::vec2 offset;    ///< Offset from the entity's position to the collision box origin
    
    /**
     * @brief Constructor for BoxColliderComponent
     * @param width Width of the collision box in pixels (default: 0)
     * @param heigth Height of the collision box in pixels (default: 0)
     * @param offset Offset vector from entity position to collision box origin (default: (0,0))
     * 
     * The offset allows the collision box to be positioned relative to the entity's
     * transform position, enabling fine-tuned collision detection that may not
     * align perfectly with the visual sprite.
     */
    BoxColliderComponent(int width = 0, int heigth = 0, glm::vec2 offset = glm::vec2(0)) {
        this->width = width;
        this->heigth = heigth;
        this->offset = offset;
    }
};

#endif // !BOXCOLLIDERCOMPONENT_HPP