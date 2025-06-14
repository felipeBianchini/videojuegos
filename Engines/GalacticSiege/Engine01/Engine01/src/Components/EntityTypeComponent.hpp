#ifndef ENTITYTYPECOMPONENT_HPP
#define ENTITYTYPECOMPONENT_HPP

#include <string>

/**
 * @brief Component to define the type of an entity.
 *
 * This can be used to categorize entities by their type ID.
 */
struct EntityTypeComponent {
	int entityType; ///< Numeric identifier representing the entity type.

    /**
     * @brief Construct a new EntityTypeComponent object.
     *
     * @param entityType Initial entity type ID (default is 0).
     */
	EntityTypeComponent(int entityType = 0) {
		this->entityType = entityType;
	}
};

#endif // !ENTITYTYPECOMPONENT_HPP
