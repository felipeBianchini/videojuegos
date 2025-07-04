/**
 * @file ClickableComponent.hpp
 * @brief Component for handling mouse click interactions on entities
 */

#ifndef CLICKABLECOMPONENT_HPP
#define CLICKABLECOMPONENT_HPP

/**
 * @struct ClickableComponent
 * @brief Component that enables entities to respond to mouse click events
 * 
 * This component allows entities to be interactive through mouse clicks.
 * It tracks the click state and can be used by UI systems or interaction
 * systems to determine when an entity has been clicked by the user.
 */
struct ClickableComponent {
    /**
     * @brief Default constructor for ClickableComponent
     * 
     * Initializes the component with IsClicked set to false,
     * indicating the entity has not been clicked yet.
     */
    ClickableComponent() {
        IsClicked = false;
    }
    
    bool IsClicked;    ///< Flag indicating whether the entity has been clicked
};

#endif //!CLICKABLECOMPONENT_HPP