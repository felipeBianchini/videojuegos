#ifndef DAMAGESYSTEM_HPP
#define DAMAGESYSTEM_HPP

#include <memory>
#include <string>
#include <iostream>

#include "../Components/CircleColliderComponent.hpp"
#include "../Components/HealthComponent.hpp"
#include "../Components/ScoreComponent.hpp"
#include "../Components/EntityTypeComponent.hpp"

#include "../ECS/ECS.hpp"
#include "../EventManager/EventManager.hpp"
#include "../Events/CollisionEvent.hpp"

class DamageSystem : public System {
public:
    DamageSystem() {
        RequiredComponent<HealthComponent>();
        RequiredComponent<CircleColliderComponent>();
        RequiredComponent<EntityTypeComponent>();
    }

    void SubscribeToCollisionEvent(std::unique_ptr<EventManager>& eventManager) {
        eventManager->SubscribeToEvent<CollisionEvent, DamageSystem>(this, &DamageSystem::OnCollision);
    }

    void OnCollision(CollisionEvent& e) {
        int aType = e.a.GetComponent<EntityTypeComponent>().entityType;
        int bType = e.b.GetComponent<EntityTypeComponent>().entityType;

        bool isPlayerHitByEnemyBullet = (aType == 1 && bType == 4);
        bool isEnemyHitByPlayerBullet = (aType == 3 && bType == 2);

        if (!isPlayerHitByEnemyBullet && !isEnemyHitByPlayerBullet) {
            return;
        }

        DealDamage(e.a, -1);
        DealDamage(e.b, -1);

        if (GetHealth(e.a) <= 0) {
            HandleEntityDeath(e.a, bType);
        }
        if (GetHealth(e.b) <= 0) {
            HandleEntityDeath(e.b, aType);
        }
    }

private:
    void DealDamage(Entity entity, int amount) {
        if (entity.HasComponent<HealthComponent>()) {
            auto& health = entity.GetComponent<HealthComponent>().health;
            health += amount;
            if (health < 0) health = 0;
        }
    }

    int GetHealth(Entity entity) const {
        if (entity.HasComponent<HealthComponent>()) {
            return entity.GetComponent<HealthComponent>().health;
        }
        return 0;
    }

    void IncreaseScore(Entity entity, int amount) {
        if (entity.HasComponent<ScoreComponent>()) {
            entity.GetComponent<ScoreComponent>().score += amount;
        }
    }

    void HandleEntityDeath(Entity deadEntity, int killerType) {
        if (killerType == 2) {
            for (auto entity : GetSystemEntiities()) {
                if (entity.HasComponent<EntityTypeComponent>() &&
                    entity.GetComponent<EntityTypeComponent>().entityType == 1) {
                    if (entity.HasComponent<ScoreComponent>() && deadEntity.HasComponent<ScoreComponent>()) {
                        IncreaseScore(entity, deadEntity.GetComponent<ScoreComponent>().score);
                    }
                    break;
                }
            }
        }
        deadEntity.Kill();
    }
};

#endif // !DAMAGESYSTEM_HPP
