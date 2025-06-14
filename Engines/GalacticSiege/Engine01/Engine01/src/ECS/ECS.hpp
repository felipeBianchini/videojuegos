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

/// Maximum number of different components supported.
const unsigned int MAX_COMPONENTS = 64;

/// Alias for component signature, represented as a bitset.
typedef std::bitset<MAX_COMPONENTS> Signature;

/**
 * @brief Base interface for components. Provides a static counter for unique IDs.
 */
struct IComponent {
protected:
	/// Static ID counter for assigning unique IDs to components.
	static int nextId;
};

/**
 * @brief Template class for components that provides a unique static ID per type.
 *
 * @tparam TComponent Component type.
 */
template <typename TComponent>
class Component : public IComponent {
public:
	/**
	 * @brief Gets the unique ID of the component type.
	 * @return int Unique component ID.
	 */
	static int GetId() {
		static int id = nextId++;
		return id;
	}
};

/**
 * @brief Represents an entity in the ECS.
 */
class Entity {
public:
	/**
	 * @brief Default constructor.
	 */
	Entity();
	/**
	 * @brief Constructor with explicit ID.
	 * @param id Entity identifier.
	 */
	Entity(int id);
	/**
	 * @brief Gets the ID of the entity.
	 * @return int Entity ID.
	 */
	int GetId() const;
	/**
	 * @brief Marks the entity as killed (to be removed).
	 */
	void Kill();
	/**
	 * @brief Checks if the entity is alive.
	 * @return true If the entity is active.
	 * @return false If the entity is marked dead.
	 */
	bool IsAlive();
	// Comparison operators by entity ID
	bool operator ==(const Entity& other) const { return id == other.id; };
	bool operator !=(const Entity& other) const { return id != other.id; };
	bool operator<(const Entity& other) const { return id < other.id; };
	bool operator>(const Entity& other) const { return id > other.id; };
	/**
	 * @brief Adds a component to the entity.
	 *
	 * @tparam TComponent Component type to add.
	 * @tparam TArgs Constructor argument types for the component.
	 * @param args Arguments forwarded to the component constructor.
	 */
	template <typename TComponent, typename... TArgs>
	void AddComponent(TArgs&&... args);
	/**
	 * @brief Removes a component from the entity.
	 *
	 * @tparam TComponent Component type to remove.
	 */
	template < typename TComponent, typename... TArgs >
	void RemoveComponent();
	/**
	 * @brief Checks if the entity has a component.
	 *
	 * @tparam TComponent Component type to check.
	 * @return true If the entity has the component.
	 * @return false Otherwise.
	 */
	template < typename TComponent, typename... TArgs >
	bool HasComponent() const;
	/**
	 * @brief Gets a reference to a component of the entity.
	 *
	 * @tparam TComponent Component type.
	 * @return TComponent& Reference to the component.
	 */
	template < typename TComponent, typename... TArgs >
	TComponent& GetComponent() const;

	/// Pointer to the registry managing this entity.
	class Registry* registry;
private:
	/// Unique entity ID.
	size_t id;
};

/**
 * @brief System that processes entities matching component requirements.
 */
class System {
public:
	System() = default;
	~System() = default;
	/**
	 * @brief Adds an entity to the system.
	 * @param entity Entity to add.
	 */
	void AddEntityToSystem(Entity entity);
	/**
	 * @brief Removes an entity from the system.
	 * @param entity Entity to remove.
	 */
	void RemoveEntityFromSystem(Entity entity);
	/**
	 * @brief Returns the entities currently registered in the system.
	 * @return std::vector<Entity> Vector of entities.
	 */
	std::vector<Entity> GetSystemEntiities() const;
	/**
	 * @brief Returns the signature of components required by this system.
	 * @return const Signature& Component signature.
	 */
	const Signature& GetComponentSignature() const;
	/**
	 * @brief Marks a component as required by the system.
	 *
	 * @tparam TComponent Component type required.
	 */
	template<typename TComponent>
	void RequiredComponent();
private:
	/// Signature of required components.
	Signature componentSignature;
	/// List of entities that match the signature.
	std::vector<Entity> entities;
};

/**
 * @brief Main registry class that manages entities, components, and systems.
 */
class Registry {
public:
	Registry();
	~Registry();
	/**
	 * @brief Updates the registry (e.g., processes entity additions/removals).
	 */
	void Update();
	/**
	 * @brief Creates a new entity.
	 * @return Entity Newly created entity.
	 */
	Entity CreateEntity();
	/**
	 * @brief Marks an entity to be killed.
	 * @param entity Entity to kill.
	 */
	void KillEntity(Entity entity);
	/**
	 * @brief Checks if an entity is alive.
	 * @param entity Entity to check.
	 * @return true If the entity is alive.
	 * @return false Otherwise.
	 */
	bool CheckIfEntityIsAlive(Entity entity);
	/**
	 * @brief Adds a component to an entity.
	 *
	 * @tparam TComponent Component type.
	 * @tparam TArgs Arguments for component constructor.
	 * @param entity Entity to add the component to.
	 * @param args Arguments forwarded to component constructor.
	 */
	template <typename TComponent, typename... TArgs>
	void AddComponent(Entity entity, TArgs&&... args);
	/**
	 * @brief Removes a component from an entity.
	 *
	 * @tparam TComponent Component type.
	 * @param entity Entity to remove the component from.
	 */
	template < typename TComponent, typename... TArgs >
	void RemoveComponent(Entity entity);
	/**
	 * @brief Checks if an entity has a specific component.
	 *
	 * @tparam TComponent Component type.
	 * @param entity Entity to check.
	 * @return true If entity has the component.
	 * @return false Otherwise.
	 */
	template < typename TComponent, typename... TArgs >
	bool HasComponent(Entity entity) const;
	/**
	 * @brief Gets a reference to a component of an entity.
	 *
	 * @tparam TComponent Component type.
	 * @param entity Entity to get component from.
	 * @return TComponent& Reference to the component.
	 */
	template < typename TComponent, typename... TArgs >
	TComponent& GetComponent(Entity entity) const;
	/**
	 * @brief Adds a system to the registry.
	 *
	 * @tparam TSystem System type.
	 * @tparam TArgs Constructor arguments for the system.
	 * @param args Arguments forwarded to system constructor.
	 */
	template <typename TSystem, typename... TArgs>
	void AddSystem(TArgs&&... args);
	/**
	 * @brief Removes a system from the registry.
	 *
	 * @tparam TSystem System type.
	 */
	template < typename TSystem>
	void RemoveSystem();
	/**
	 * @brief Checks if a system exists in the registry.
	 *
	 * @tparam TSystem System type.
	 * @return true If the system exists.
	 * @return false Otherwise.
	 */
	template < typename TSystem>
	bool HasSystem() const;
	/**
	 * @brief Gets a reference to a system.
	 *
	 * @tparam TSystem System type.
	 * @return TSystem& Reference to the system.
	 */
	template < typename TSystem>
	TSystem& GetSystem() const;
	/**
	 * @brief Adds an entity to all relevant systems.
	 * @param entity Entity to add.
	 */
	void AddEntityToSystems(Entity entity);
	/**
	 * @brief Removes an entity from all systems.
	 * @param entity Entity to remove.
	 */
	void RemoveEntityFromSystems(Entity entity);
	/**
	 * @brief Clears all entities and resets the registry.
	 */
	void ClearAllEntities();

private:
	/// Number of active entities.
	unsigned int numEntity = 0;
	/// Pools of components, indexed by component ID.
	std::vector<std::shared_ptr<IPool>> componentsPools;
	/// Signatures of components for each entity.
	std::vector<Signature> entityComponentSignatures;
	/// Systems stored by their type.
	std::unordered_map<std::type_index, std::shared_ptr<System>> systems;
	/// Entities queued to be added.
	std::set<Entity> entitiesToBeAdded;
	/// Entities queued to be killed.
	std::set<Entity> entitiesToBeKilled;
	/// Free entity IDs for reuse.
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
		componentPool->Resize(entityId + 100);
	}
	TComponent newComponent(std::forward<TArgs>(args)...);
	componentPool->Set(entityId, newComponent);
	entityComponentSignatures[entityId].set(componentId);
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
	if (entityId < 0 || entityId >= entityComponentSignatures.size()) {
		return false;
	}
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