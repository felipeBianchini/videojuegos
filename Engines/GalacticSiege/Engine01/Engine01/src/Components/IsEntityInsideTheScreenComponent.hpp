#ifndef ISENTITYINSIDETHESCREENCOMPONENT_HPP
#define ISENTITYINSIDETHESCREENCOMPONENT_HPP

/**
 * @brief Component to track if an entity is currently inside the screen bounds.
 */
struct IsEntityInsideTheScreenComponent {
	bool isEntityInsideTheScreen; ///< True if the entity is inside the screen, false otherwise.

    /**
     * @brief Construct a new IsEntityInsideTheScreenComponent object
     *
     * @param isInside Initial state, true if inside the screen (default false).
     */
	IsEntityInsideTheScreenComponent(bool isInside = false) {
		this->isEntityInsideTheScreen = isInside;
	}
};

#endif // !ISENTITYINSIDETHESCREENCOMPONENT_HPP