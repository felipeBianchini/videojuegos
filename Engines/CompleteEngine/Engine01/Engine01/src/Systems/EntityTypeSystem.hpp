#ifndef ENTITYTYPESYSTEM_HPP
#define ENTITYTYPESYSTEM_HPP

#include "../ECS/ECS.hpp"
#include "../Components/EntityTypeComponent.hpp"

class EntityTypeSystem : public System {
	EntityTypeSystem() {
		RequiredComponent<EntityTypeComponent>();
	}
	int GetEntityType(Entity entity) {
		if (entity.HasComponent<EntityTypeComponent>()) {
			return entity.GetComponent<EntityTypeComponent>().entityType;
		}
	}
};

#endif // !ENTITYTYPESYSTEM_HPP
