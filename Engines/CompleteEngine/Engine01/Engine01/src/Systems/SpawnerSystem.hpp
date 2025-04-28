#ifndef SPAWNERSYSTEM_HPP
#define SPAWNERSYSTEM_HPP

#include "../ECS/ECS.hpp"

class SpawnerSystem : public System {
public:
	SpawnerSystem() {
		RequiredComponent<>();
	}
	Update() {

	}
private:
	
};

#endif // !SPAWNERSYSTEM_HPP