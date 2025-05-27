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
        bool isPlayerAttackedByEnemy = (aType == 1 && bType == 5);
        bool playerGatheredPowerUp = (aType == 1 && bType == 10) || (aType == 1 && bType == 11);
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
        else if (playerGatheredPowerUp) {
            if (bType == 10) {
                GainLife(e.a, e.b);
            }
            else if (bType == 11) {
                Nuke(e.b);
            }
        }
    }

    void PlaySoundEffect(std::string soundEffectId) {
        Mix_Chunk* soundEffect = Game::GetInstance().assetManager->GetSoundEffect(soundEffectId);
        if (soundEffect) {
            Mix_VolumeChunk(soundEffect, 75);
            Mix_PlayChannel(-1, soundEffect, 0);
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
        PlaySoundEffect("powerUp_pickUp");
    }

    void Nuke(Entity nuke) {
        for (auto entity : GetSystemEntiities()) {
            if (entity.HasComponent<EntityTypeComponent>()) {
                int type = entity.GetComponent<EntityTypeComponent>().entityType;
                if (type == 3 || type == 5 || type == 6) {
                    if (entity.IsAlive()) {
                        EnemyExplosionAnimation(entity, true);
                        entity.Kill();
                    }
                }
            }
        }
        nuke.Kill();
        PlaySoundEffect("powerUp_pickUp");
        CreateExplosion();
    }

    void CreateExplosion() {
        const int frameWidth = 128;
        const int frameHeight = 128;
        const float scale = 4.0f;
        const int screenWidth = Game::GetInstance().window_width;
        const int screenHeight = Game::GetInstance().window_height;
        glm::vec2 position(
            (screenWidth / 2.0f) - (frameWidth * scale / 2.0f),
            (screenHeight / 2.0f) - (frameHeight * scale / 2.0f)
        );
        Entity explosion = Game::GetInstance().registry->CreateEntity();
        explosion.AddComponent<RigidBodyComponent>(glm::vec2(0, 0));
        explosion.AddComponent<SpriteComponent>("explosion", frameWidth, frameHeight, 0, 0);
        explosion.AddComponent<TransformComponent>(position, glm::vec2(scale, scale), 0.0);
        explosion.AddComponent<AnimationComponent>(12, 4);
        explosion.AddComponent<EntityTypeComponent>(12);
        PlaySoundEffect("explosion");
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
        EnemyExplosionAnimation(deadEntity);
        if (deadEntity.GetComponent<EntityTypeComponent>().entityType != 7) deadEntity.Kill();
    }

    void EnemyExplosionAnimation(Entity enemy, bool massiveKill = false) {
        const int frameWidth = 152;
        const int frameHeight = 166;
        const float scale = 1.0f;
        auto& transform = enemy.GetComponent<TransformComponent>();
        glm::vec2 position(
            transform.position.x,
            transform.position.y
        );
        Entity explosion = Game::GetInstance().registry->CreateEntity();
        explosion.AddComponent<RigidBodyComponent>(glm::vec2(0, 0));
        explosion.AddComponent<SpriteComponent>("enemydeath2", frameWidth, frameHeight, 0, 0);
        explosion.AddComponent<TransformComponent>(position, glm::vec2(scale, scale), 0.0);
        explosion.AddComponent<AnimationComponent>(11, 11);
        explosion.AddComponent<EntityTypeComponent>(12);
        if (!massiveKill) {
            PlaySoundEffect("enemy_death");
        }
    }

    void EnemyAttack(Entity player, Entity enemy2) {
        if (!player.IsAlive() || !enemy2.IsAlive()) return;
        int damageDone = 0;
        int entityType = enemy2.GetComponent<EntityTypeComponent>().entityType;
        if (entityType == 5) {
            damageDone = 2;
            enemy2.Kill();
            PlaySoundEffect("enemy_death");
        }
        DealDamage(player, damageDone);
    }
};

#endif // !DAMAGESYSTEM_HPP