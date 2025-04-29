#ifndef HEALTHSYSTEM_HPP
#define HEALTHSYSTEM_HPP

#include "../ECS/ECS.hpp"
#include "../Components/HealthComponent.hpp"

class HealthSystem : public System {
    HealthSystem() {
        RequiredComponent<HealthComponent>();
    }

    void LoseHealth(Entity entity, int healthLost) {
        if (entity.HasComponent<HealthComponent>()) {
            auto& health = entity.GetComponent<HealthComponent>().health;
            health -= healthLost;
        }
    }

    void GainHealth(Entity entity, int healthGained) {
        if (entity.HasComponent<HealthComponent>()) {
            auto& health = entity.GetComponent<HealthComponent>().health;
            health += healthGained;
        }
    }

    int GetHealth(Entity entity) {
        if (entity.HasComponent<HealthComponent>()) {
            return entity.GetComponent<HealthComponent>().health;
        }
    }
};

#endif // !HEALTHSYSTEM_HPP
