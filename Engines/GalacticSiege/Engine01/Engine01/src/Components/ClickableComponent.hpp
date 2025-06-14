#ifndef CLICKABLECOMPONENT_HPP
#define CLICKABLECOMPONENT_HPP

/**
 * @brief Component that marks an entity as clickable.
 *
 * Contains the state whether the entity has been clicked.
 */
struct ClickableComponent {
    bool IsClicked; ///< Indicates if the entity has been clicked.

    /**
     * @brief Construct a new ClickableComponent object.
     *
     * Initializes IsClicked to false.
     */
	ClickableComponent() {
		IsClicked = false;
	}
};

#endif //!CLICKABLECOMPONENT_HPP