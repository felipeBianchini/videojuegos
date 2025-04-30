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

const unsigned int MAX_COMPONENTS = 64;

// Signature
typedef std::bitset<MAX_COMPONENTS> Signature;

struct IComponent {
protected:
	static int nextId;
};

template <typename TComponent>
class Component : public IComponent {
public:
	static int GetId() {
		static int id = nextId++;
		return id;
	}
};

class Entity {
public:
	Entity();
	Entity(int id);
	int GetId() const;
	void Kill();
	bool operator ==(const Entity& other) const { return id == other.id; };
	bool operator !=(const Entity& other) const { return id != other.id; };
	bool operator<(const Entity& other) const { return id < other.id; };
	bool operator>(const Entity& other) const { return id > other.id; };
	template <typename TComponent, typename... TArgs>
	void AddComponent(TArgs&&... args);
	template < typename TComponent, typename... TArgs >
	void RemoveComponent();
	template < typename TComponent, typename... TArgs >
	bool HasComponent() const;
	template < typename TComponent, typename... TArgs >
	TComponent& GetComponent() const;

	class Registry* registry;
private:
	size_t id;
};

class System {
public:
	System() = default;
	~System() = default;

	void AddEntityToSystem(Entity entity);
	void RemoveEntityFromSystem(Entity entity);
	std::vector<Entity> GetSystemEntiities() const;
	const Signature& GetComponentSignature() const;

	template<typename TComponent>
	void RequiredComponent();
private:
	Signature componentSignature;
	std::vector<Entity> entities;

};

class Registry {
public:
	Registry();
	~Registry();
	void Update();
	// Entity Management
	Entity CreateEntity();
	void KillEntity(Entity entity);
	// Component Management
	template <typename TComponent, typename... TArgs>
	void AddComponent(Entity entity, TArgs&&... args);
	template < typename TComponent, typename... TArgs >
	void RemoveComponent(Entity entity);
	template < typename TComponent, typename... TArgs >
	bool HasComponent(Entity entity) const;
	template < typename TComponent, typename... TArgs >
	TComponent& GetComponent(Entity entity) const;
	// Systems Management
	template <typename TSystem, typename... TArgs>
	void AddSystem(TArgs&&... args);
	template < typename TSystem>
	void RemoveSystem();
	template < typename TSystem>
	bool HasSystem() const;
	template < typename TSystem>
	TSystem& GetSystem() const;

	// Add and Remove entities to systems
	void AddEntityToSystems(Entity entity);
	void RemoveEntityFromSystems(Entity entity);

	// Reset Registry
	void ClearAllEntities();

private:
	unsigned int numEntity = 0;
	std::vector<std::shared_ptr<IPool>> componentsPools;
	std::vector<Signature> entityComponentSignatures;

	std::unordered_map<std::type_index, std::shared_ptr<System>> systems;

	std::set<Entity> entitiesToBeAdded;
	std::set<Entity> entitiesToBeKilled;

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
		//std::cerr << "error " << entityId << std::endl;;
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