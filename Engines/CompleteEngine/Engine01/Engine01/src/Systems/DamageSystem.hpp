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
        if (!e.a.IsAlive() || !e.b.IsAlive()) return;
        if (!e.a.HasComponent<EntityTypeComponent>() || !e.b.HasComponent<EntityTypeComponent>()) return;
        int aType = e.a.GetComponent<EntityTypeComponent>().entityType;
        int bType = e.b.GetComponent<EntityTypeComponent>().entityType;
        bool isPlayerHitByEnemyBullet = (aType == 1 && bType == 4);
        bool isEnemyHitByPlayerBullet = (aType == 3 && bType == 2) || (aType == 5 && bType == 2) ||
            (aType == 6 && bType == 2) || (aType == 7 && bType == 2);
        bool isPlayerAttackedByEnemy = (aType == 1 && bType == 5) || (aType == 1 && bType == 6);
        bool playerGatheredExtraLife = (aType == 1 && bType == 10);
        if (isPlayerHitByEnemyBullet || isEnemyHitByPlayerBullet) {
            DealDamage(e.a, 1);
            if (GetHealth(e.a) <= 0 && e.a.IsAlive()) {
                HandleEntityDeath(e.a, bType);
            }
            e.b.Kill();
        }
        else if (isPlayerAttackedByEnemy ) {
            EnemyAttack(e.a, e.b);
        }
        else if (playerGatheredExtraLife) {
            GainLife(e.a, e.b);
        }
    }

private:
    void DealDamage(Entity entity, int amount) {
        if (!entity.IsAlive()) return;
        if (entity.HasComponent<HealthComponent>()) {
            auto& health = entity.GetComponent<HealthComponent>().health;
            health -= amount;
            if (health < 0) health = 0;
        }
    }

    void GainLife(Entity player, Entity extraLife) {
        player.GetComponent<HealthComponent>().health += 1;
        extraLife.Kill();
    }

    int GetHealth(Entity entity) const {
        if (!entity.IsAlive()) return 0;
        if (entity.HasComponent<HealthComponent>()) {
            return entity.GetComponent<HealthComponent>().health;
        }
        return 0;
    }

    void IncreaseScore(Entity entity, int amount) {
        if (!entity.IsAlive()) return;
        if (entity.HasComponent<ScoreComponent>()) {
            entity.GetComponent<ScoreComponent>().score += amount;
        }
    }

    void HandleEntityDeath(Entity deadEntity, int killerType) {
        if (!deadEntity.IsAlive()) return;
        if (killerType == 2) {
            for (auto entity : GetSystemEntiities()) {
                if (!entity.IsAlive()) continue;

                if (entity.HasComponent<EntityTypeComponent>() &&
                    entity.GetComponent<EntityTypeComponent>().entityType == 1) {

                    if (entity.HasComponent<ScoreComponent>() &&
                        deadEntity.HasComponent<ScoreComponent>()) {
                        IncreaseScore(entity, deadEntity.GetComponent<ScoreComponent>().score);
                    }
                    break;
                }
            }
        }
        deadEntity.Kill();
    }

    void EnemyAttack(Entity player, Entity enemy2) {
        if (!player.IsAlive() || !enemy2.IsAlive()) return;
        int damageDone = 0;
        int entityType = enemy2.GetComponent<EntityTypeComponent>().entityType;
        if (entityType == 5) {
            damageDone = -2;
            enemy2.Kill();
        }
        else if (entityType == 6) {
            damageDone = -3;
        }
        DealDamage(player, 3);
    }
};

#endif // !DAMAGESYSTEM_HPP