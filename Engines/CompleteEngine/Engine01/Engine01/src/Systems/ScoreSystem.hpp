#ifndef SCORESYSTEM_HPP
#define SCORESYSTEM_HPP

#include "../ECS/ECS.hpp"
#include "../Components/ScoreComponent.hpp"

class ScoreSystem : public System {
	ScoreSystem() {
		RequiredComponent<ScoreComponent>();
	}
	void AddScore(Entity entity, int points) {
		if (entity.HasComponent<ScoreComponent>()) {
			entity.GetComponent<ScoreComponent>().score += points;
		}
	}
	int GetScore(Entity entity) {
		if (entity.HasComponent<ScoreComponent>()) {
			return entity.GetComponent<ScoreComponent>().score;
		}
	}
};

#endif // !SCORESYSTEM_HPP
