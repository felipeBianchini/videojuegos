/**
 * @file CircleColliderComponent.hpp
 * @brief Component for circular collision detection in the ECS system
 */

#ifndef CIRCLECOLLIDERCOMPONENT_HPP
#define CIRCLECOLLIDERCOMPONENT_HPP

/**
 * @struct CircleColliderComponent
 * @brief Component that defines a circular collision area for entities
 * 
 * This component provides circular collision detection capabilities by defining
 * a collision circle with a specified radius. The width and height parameters
 * may be used for additional collision calculations or rendering purposes.
 */
struct CircleColliderComponent {
    int radius;    ///< Radius of the circular collision area in pixels
    int width;     ///< Width parameter for collision calculations
    int height;    ///< Height parameter for collision calculations
    
    /**
     * @brief Constructor for CircleColliderComponent
     * @param radius Radius of the circular collision area in pixels (default: 0)
     * @param width Width parameter for collision calculations (default: 0)
     * @param height Height parameter for collision calculations (default: 0)
     */
    CircleColliderComponent(int radius = 0, int width = 0, int height = 0) {
        this->radius = radius;
        this->width = width;
        this->height = height;
    }
};

#endif // !CIRCLECOLLIDERCOMPONENT_HPP