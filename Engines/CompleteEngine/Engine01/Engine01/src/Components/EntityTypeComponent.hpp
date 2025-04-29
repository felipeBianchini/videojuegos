#ifndef ENTITYTYPECOMPONENT_HPP
#define ENTITYTYPECOMPONENT_HPP

#include <string>

struct EntityTypeComponent {
	int entityType;
	EntityTypeComponent(int entityType = 0) {
		this->entityType = entityType;
	}
};

#endif // !ENTITYTYPECOMPONENT_HPP
