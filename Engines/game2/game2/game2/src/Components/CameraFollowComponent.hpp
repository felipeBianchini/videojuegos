/**
 * @file CameraFollowComponent.hpp
 * @brief Component for marking entities to be followed by the camera
 */

#ifndef CAMERAFOLLOWCOMPONENT_HPP
#define CAMERAFOLLOWCOMPONENT_HPP

/**
 * @struct CameraFollowComponent
 * @brief Tag component that marks an entity to be followed by the camera system
 * 
 * This is a marker component used to identify which entity the camera should follow.
 * It contains no data and serves purely as a flag for the camera system to recognize
 * the target entity. Typically attached to the player or main character entity.
 */
struct CameraFollowComponent {
    /**
     * @brief Default constructor for CameraFollowComponent
     * 
     * Creates an empty marker component with no initialization required.
     * The presence of this component on an entity signals to the camera system
     * that this entity should be the camera's follow target.
     */
    CameraFollowComponent() {}
};

#endif // !CAMERAFOLLOWCOMPONENT_HPP