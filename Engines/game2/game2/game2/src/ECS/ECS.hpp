#ifndef ECS_HPP
#define ECS_HPP

#include <cstddef>
#include <bitset>
#include <vector>
#include <memory>
#include <unordered_map>
#include <set>
#include <deque>
#include <typeindex>
#include <iostream>

#include "../Utils/Pool.hpp"

/**
 * @brief Maximum number of components that can be registered in the ECS.
 */
const unsigned int MAX_COMPONENTS = 64;

/**
 * @brief A bitset representing which components an entity has.
 */
typedef std::bitset<MAX_COMPONENTS> Signature;

/**
 * @brief Base interface for all components in the ECS.
 * 
 * This interface provides a common base for all components and manages
 * unique component ID generation.
 */
struct IComponent {
protected:
	/**
	 * @brief Static counter for generating unique component IDs.
	 */
	static int nextId;
};

/**
 * @brief Template class for creating typed components.
 * 
 * This template provides unique ID generation for each component type
 * in the ECS system.
 * 
 * @tparam TComponent The component type.
 */
template <typename TComponent>
class Component : public IComponent {
public:
	/**
	 * @brief Gets the unique ID for this component type.
	 * 
	 * @return The unique identifier for this component type.
	 */
	static int GetId() {
		static int id = nextId++;
		return id;
	}
};

/**
 * @brief Represents an entity in the ECS system.
 * 
 * An entity is a unique identifier that can have components attached to it.
 * It provides methods for managing its components through the registry.
 */
class Entity {
public:
	/**
	 * @brief Default constructor for Entity.
	 */
	Entity();
	
	/**
	 * @brief Constructs an Entity with a specific ID.
	 * 
	 * @param id The unique identifier for this entity.
	 */
	Entity(int id);
	
	/**
	 * @brief Gets the unique ID of this entity.
	 * 
	 * @return The entity's unique identifier.
	 */
	int GetId() const;
	
	/**
	 * @brief Marks this entity for destruction.
	 */
	void Kill();
	
	/**
	 * @brief Equality comparison operator.
	 * 
	 * @param other The entity to compare with.
	 * @return True if entities have the same ID, false otherwise.
	 */
	bool operator ==(const Entity& other) const { return id == other.id; };
	
	/**
	 * @brief Inequality comparison operator.
	 * 
	 * @param other The entity to compare with.
	 * @return True if entities have different IDs, false otherwise.
	 */
	bool operator !=(const Entity& other) const { return id != other.id; };
	
	/**
	 * @brief Less than comparison operator.
	 * 
	 * @param other The entity to compare with.
	 * @return True if this entity's ID is less than the other's.
	 */
	bool operator<(const Entity& other) const { return id < other.id; };
	
	/**
	 * @brief Greater than comparison operator.
	 * 
	 * @param other The entity to compare with.
	 * @return True if this entity's ID is greater than the other's.
	 */
	bool operator>(const Entity& other) const { return id > other.id; };
	
	/**
	 * @brief Adds a component to this entity.
	 * 
	 * @tparam TComponent The type of component to add.
	 * @tparam TArgs The types of arguments for component construction.
	 * @param args Arguments to forward to the component constructor.
	 */
	template <typename TComponent, typename... TArgs>
	void AddComponent(TArgs&&... args);
	
	/**
	 * @brief Removes a component from this entity.
	 * 
	 * @tparam TComponent The type of component to remove.
	 * @tparam TArgs Unused template parameters for consistency.
	 */
	template < typename TComponent, typename... TArgs >
	void RemoveComponent();
	
	/**
	 * @brief Checks if this entity has a specific component.
	 * 
	 * @tparam TComponent The type of component to check for.
	 * @tparam TArgs Unused template parameters for consistency.
	 * @return True if the entity has the component, false otherwise.
	 */
	template < typename TComponent, typename... TArgs >
	bool HasComponent() const;
	
	/**
	 * @brief Gets a reference to a component attached to this entity.
	 * 
	 * @tparam TComponent The type of component to retrieve.
	 * @tparam TArgs Unused template parameters for consistency.
	 * @return Reference to the component.
	 */
	template < typename TComponent, typename... TArgs >
	TComponent& GetComponent() const;

	/**
	 * @brief Pointer to the registry that manages this entity.
	 */
	class Registry* registry;
private:
	/**
	 * @brief The unique identifier for this entity.
	 */
	int id;
};

/**
 * @brief Base class for all systems in the ECS.
 * 
 * A system operates on entities that have specific components.
 * It maintains a list of entities that match its component requirements.
 */
class System {
public:
	/**
	 * @brief Default constructor for System.
	 */
	System() = default;
	
	/**
	 * @brief Default destructor for System.
	 */
	~System() = default;

	/**
	 * @brief Adds an entity to this system.
	 * 
	 * @param entity The entity to add to the system.
	 */
	void AddEntityToSystem(Entity entity);
	
	/**
	 * @brief Removes an entity from this system.
	 * 
	 * @param entity The entity to remove from the system.
	 */
	void RemoveEntityFromSystem(Entity entity);
	
	/**
	 * @brief Gets all entities currently in this system.
	 * 
	 * @return Vector of entities that belong to this system.
	 */
	std::vector<Entity> GetSystemEntiities() const;
	
	/**
	 * @brief Gets the component signature for this system.
	 * 
	 * @return The signature indicating which components are required.
	 */
	const Signature& GetComponentSignature() const;

	/**
	 * @brief Marks a component type as required for this system.
	 * 
	 * @tparam TComponent The component type to require.
	 */
	template<typename TComponent>
	void RequiredComponent();
private:
	/**
	 * @brief Bitset indicating which components are required by this system.
	 */
	Signature componentSignature;
	
	/**
	 * @brief List of entities that belong to this system.
	 */
	std::vector<Entity> entities;

};

/**
 * @brief Central registry for managing entities, components, and systems.
 * 
 * The Registry is the core of the ECS system, responsible for creating
 * and managing entities, their components, and the systems that operate on them.
 */
class Registry {
public:
	/**
	 * @brief Constructs a new Registry.
	 */
	Registry();
	
	/**
	 * @brief Destructs the Registry and cleans up resources.
	 */
	~Registry();
	
	/**
	 * @brief Updates the registry by processing pending entity operations.
	 */
	void Update();
	
	/**
	 * @brief Creates a new entity in the registry.
	 * 
	 * @return The newly created entity.
	 */
	Entity CreateEntity();
	
	/**
	 * @brief Marks an entity for destruction.
	 * 
	 * @param entity The entity to destroy.
	 */
	void KillEntity(Entity entity);
	
	/**
	 * @brief Adds a component to an entity.
	 * 
	 * @tparam TComponent The type of component to add.
	 * @tparam TArgs The types of arguments for component construction.
	 * @param entity The entity to add the component to.
	 * @param args Arguments to forward to the component constructor.
	 */
	template <typename TComponent, typename... TArgs>
	void AddComponent(Entity entity, TArgs&&... args);
	
	/**
	 * @brief Removes a component from an entity.
	 * 
	 * @tparam TComponent The type of component to remove.
	 * @tparam TArgs Unused template parameters for consistency.
	 * @param entity The entity to remove the component from.
	 */
	template < typename TComponent, typename... TArgs >
	void RemoveComponent(Entity entity);
	
	/**
	 * @brief Checks if an entity has a specific component.
	 * 
	 * @tparam TComponent The type of component to check for.
	 * @tparam TArgs Unused template parameters for consistency.
	 * @param entity The entity to check.
	 * @return True if the entity has the component, false otherwise.
	 */
	template < typename TComponent, typename... TArgs >
	bool HasComponent(Entity entity) const;
	
	/**
	 * @brief Gets a reference to a component attached to an entity.
	 * 
	 * @tparam TComponent The type of component to retrieve.
	 * @tparam TArgs Unused template parameters for consistency.
	 * @param entity The entity to get the component from.
	 * @return Reference to the component.
	 */
	template < typename TComponent, typename... TArgs >
	TComponent& GetComponent(Entity entity) const;
	
	/**
	 * @brief Adds a system to the registry.
	 * 
	 * @tparam TSystem The type of system to add.
	 * @tparam TArgs The types of arguments for system construction.
	 * @param args Arguments to forward to the system constructor.
	 */
	template <typename TSystem, typename... TArgs>
	void AddSystem(TArgs&&... args);
	
	/**
	 * @brief Removes a system from the registry.
	 * 
	 * @tparam TSystem The type of system to remove.
	 */
	template < typename TSystem>
	void RemoveSystem();
	
	/**
	 * @brief Checks if a system exists in the registry.
	 * 
	 * @tparam TSystem The type of system to check for.
	 * @return True if the system exists, false otherwise.
	 */
	template < typename TSystem>
	bool HasSystem() const;
	
	/**
	 * @brief Gets a reference to a system in the registry.
	 * 
	 * @tparam TSystem The type of system to retrieve.
	 * @return Reference to the system.
	 */
	template < typename TSystem>
	TSystem& GetSystem() const;

	/**
	 * @brief Adds an entity to all systems that match its component signature.
	 * 
	 * @param entity The entity to add to matching systems.
	 */
	void AddEntityToSystems(Entity entity);
	
	/**
	 * @brief Removes an entity from all systems.
	 * 
	 * @param entity The entity to remove from systems.
	 */
	void RemoveEntityFromSystems(Entity entity);

	/**
	 * @brief Destroys all entities and clears the registry.
	 */
	void ClearAllEntities();

private:
	/**
	 * @brief Counter for the total number of entities created.
	 */
	int numEntity = 0;
	
	/**
	 * @brief Storage pools for all component types.
	 */
	std::vector<std::shared_ptr<IPool>> componentsPools;
	
	/**
	 * @brief Component signatures for each entity.
	 */
	std::vector<Signature> entityComponentSignatures;

	/**
	 * @brief Map of all systems indexed by their type.
	 */
	std::unordered_map<std::type_index, std::shared_ptr<System>> systems;

	/**
	 * @brief Set of entities waiting to be added to systems.
	 */
	std::set<Entity> entitiesToBeAdded;
	
	/**
	 * @brief Set of entities waiting to be destroyed.
	 */
	std::set<Entity> entitiesToBeKilled;

	/**
	 * @brief Queue of entity IDs available for reuse.
	 */
	std::deque<int> freeIds;
};

template<typename TComponent>
void System::RequiredComponent()
{
	const int componentId = Component<TComponent>::GetId();
	componentSignature.set(componentId);
}

template<typename TComponent, typename ...TArgs>
void Registry::AddComponent(Entity entity, TArgs && ...args)
{
	const size_t componentId = Component<TComponent>::GetId();
	const int entityId = entity.GetId();
	if (static_cast<long unsigned int>(componentId) >= componentsPools.size()) {
		componentsPools.resize(componentId + 10, nullptr);
	}
	if (!componentsPools[componentId]) {
		std::shared_ptr<Pool<TComponent>> newComponentPool = std::make_shared<Pool<TComponent>>();
		componentsPools[componentId] = newComponentPool;
	}
	std::shared_ptr<Pool<TComponent>> componentPool = 
		std::static_pointer_cast<Pool<TComponent>>(componentsPools[componentId]);
	if (entityId >= componentPool->GetSize()) {
		componentPool->Resize(numEntity + 100);
	}
	TComponent newComponent(std::forward<TArgs>(args)...);
	componentPool->Set(entityId, newComponent);
	entityComponentSignatures[entityId].set(componentId);
	//std::cout << "[Registry] Se agrega componente " << componentId << " a la entidad " << entityId << std::endl;
}

template<typename TComponent, typename ...TArgs>
void Registry::RemoveComponent(Entity entity)
{
	const int componentId = Component<TComponent>::GetId();
	const int entityId = entity.GetId();
	entityComponentSignatures[entityId].set(componentId, false);
}

template<typename TComponent, typename ...TArgs>
bool Registry::HasComponent(Entity entity) const
{
	const int componentId = Component<TComponent>::GetId();
	const int entityId = entity.GetId();
	return entityComponentSignatures[entityId].test(componentId);
}

template<typename TComponent, typename ...TArgs>
TComponent& Registry::GetComponent(Entity entity) const
{
	const int componentId = Component<TComponent>::GetId();
	const int entityId = entity.GetId();
	auto componentPool = std::static_pointer_cast<Pool<TComponent>>(componentsPools[componentId]);
	return componentPool->Get(entityId);
}

template<typename TSystem, typename ...TArgs>
void Registry::AddSystem(TArgs && ...args)
{
	std::shared_ptr<TSystem> newSystem = std::make_shared<TSystem>(std::forward<TArgs>(args)...);
	systems.insert(std::make_pair(std::type_index(typeid(TSystem)), newSystem));
}

template<typename TSystem>
void Registry::RemoveSystem()
{
	auto system = systems.find(std::type_index(typeid(TSystem)));
	systems.erase(system); 
}

template<typename TSystem>
bool Registry::HasSystem() const
{
	return systems.find(std::type_index(typeid(TSystem))) != systems.end(); 
}

template<typename TSystem>
TSystem& Registry::GetSystem() const
{
	auto system = systems.find(std::type_index(typeid(TSystem)));
	return *(std::static_pointer_cast<TSystem>(system->second));
}

template<typename TComponent, typename ...TArgs>
void Entity::AddComponent(TArgs && ...args)
{
	registry->AddComponent<TComponent>(*this, std::forward<TArgs>(args)...);
}

template<typename TComponent, typename ...TArgs>
void Entity::RemoveComponent()
{
	registry->RemoveComponent<TComponent>(*this);
}

template<typename TComponent, typename ...TArgs>
bool Entity::HasComponent() const
{
	return registry->HasComponent<TComponent>(*this);
}

template<typename TComponent, typename ...TArgs>
TComponent& Entity::GetComponent() const
{
	return registry->GetComponent<TComponent>(*this);
}

#endif // !ECS_HPP