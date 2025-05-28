#ifndef HEALTHCOMPONENT_HPP
#define HEALTHCOMPONENT_HPP


/**
 * @brief Component representing an entity's health.
 */
struct HealthComponent {
    int health; ///< Current health value of the entity.

    /**
     * @brief Construct a new HealthComponent object
     *
     * @param health Initial health value (default is 0).
     */
	HealthComponent(int health = 0) {
		this->health = health;
	}
};

#endif // !HEALTHCOMPONENT_HPP
