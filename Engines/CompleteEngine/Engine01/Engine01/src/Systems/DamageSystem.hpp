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

/**
 * @class DamageSystem
 * @brief A system for handling damage and collision events in an Entity-Component-System (ECS) architecture.
 *
 * This system manages entities with HealthComponent, CircleColliderComponent, and EntityTypeComponent.
 * It processes collision events to apply damage, handle entity deaths, trigger power-ups, and create visual
 * and audio effects such as explosions and sound effects.
 */
class DamageSystem : public System {
public:
    /**
     * @brief Constructor for the DamageSystem.
     *
     * Initializes the system and specifies that entities must have HealthComponent, CircleColliderComponent,
     * and EntityTypeComponent to be managed.
     */
    DamageSystem() {
        RequiredComponent<HealthComponent>();
        RequiredComponent<CircleColliderComponent>();
        RequiredComponent<EntityTypeComponent>();
    }
    /**
     * @brief Subscribes the system to collision events.
     *
     * Registers the system to handle CollisionEvent notifications via the event manager.
     *
     * @param eventManager A unique pointer to the EventManager instance.
     */
    void SubscribeToCollisionEvent(std::unique_ptr<EventManager>& eventManager) {
        eventManager->SubscribeToEvent<CollisionEvent, DamageSystem>(this, &DamageSystem::OnCollision);
    }
    /**
     * @brief Handles collision events between entities.
     *
     * Processes collisions to determine interactions such as player hit by enemy bullets, enemy hit by player
     * bullets, player attacked by enemies, power-up collection, or projectile collisions. Applies damage,
     * updates scores, and triggers appropriate effects.
     *
     * @param e The CollisionEvent containing the two colliding entities.
     */
    void OnCollision(CollisionEvent& e) {
        if (!e.a.IsAlive() || !e.b.IsAlive()) return;
        if (!e.a.HasComponent<EntityTypeComponent>() || !e.b.HasComponent<EntityTypeComponent>()) return;
        int aType = e.a.GetComponent<EntityTypeComponent>().entityType;
        int bType = e.b.GetComponent<EntityTypeComponent>().entityType;
        bool isPlayerHitByEnemyBullet = (aType == 1 && bType == 4) || (aType == 1 && bType == 13);
        bool isEnemyHitByPlayerBullet = (aType == 3 && bType == 2) || (aType == 5 && bType == 2) ||
            (aType == 6 && bType == 2) || (aType == 7 && bType == 2);
        bool isPlayerAttackedByEnemy = (aType == 1 && bType == 5);
        bool playerGatheredPowerUp = (aType == 1 && bType == 10) || (aType == 1 && bType == 11);
        bool projectilesCollision = (aType == 13 && bType == 2);
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
        else if (projectilesCollision) {
            e.b.Kill();
        }
    }
    /**
     * @brief Plays a sound effect using the asset manager.
     *
     * Retrieves and plays a sound effect with the specified ID at a set volume.
     *
     * @param soundEffectId The ID of the sound effect to play.
     */
    void PlaySoundEffect(std::string soundEffectId) {
        Mix_Chunk* soundEffect = Game::GetInstance().assetManager->GetSoundEffect(soundEffectId);
        if (soundEffect) {
            Mix_VolumeChunk(soundEffect, 75);
            Mix_PlayChannel(-1, soundEffect, 0);
        }
    }

private:
    /**
     * @brief Applies damage to an entity.
     *
     * Reduces the health of the specified entity by the given amount, ensuring health does not go below zero.
     *
     * @param entity The entity to damage.
     * @param amount The amount of damage to deal.
     */
    void DealDamage(Entity entity, int amount) {
        if (!entity.IsAlive()) return;
        if (entity.HasComponent<HealthComponent>()) {
            auto& health = entity.GetComponent<HealthComponent>().health;
            health -= amount;
            if (health < 0) health = 0;
        }
    }
    /**
     * @brief Increases the player's health upon collecting an extra life power-up.
     *
     * Adds one health point to the player and marks the power-up for deletion, playing a sound effect.
     *
     * @param player The player entity.
     * @param extraLife The extra life power-up entity.
     */
    void GainLife(Entity player, Entity extraLife) {
        player.GetComponent<HealthComponent>().health += 1;
        extraLife.Kill();
        PlaySoundEffect("powerUp_pickUp");
    }
    /**
     * @brief Activates a nuke power-up, destroying all enemies.
     *
     * Destroys all enemy entities (types 3, 5, 6), triggers explosion animations, marks the nuke for deletion,
     * and plays sound effects.
     *
     * @param nuke The nuke power-up entity.
     */
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
    /**
     * @brief Creates a large explosion effect at the center of the screen.
     *
     * Creates an explosion entity with appropriate components for animation and plays an explosion sound effect.
     */
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
    /**
     * @brief Retrieves the current health of an entity.
     *
     * Returns the health of the specified entity if it has a HealthComponent and is alive.
     *
     * @param entity The entity whose health is queried.
     * @return The current health of the entity, or 0 if the entity is not alive or lacks a HealthComponent.
     */
    int GetHealth(Entity entity) const {
        if (!entity.IsAlive()) return 0;
        if (entity.HasComponent<HealthComponent>()) {
            return entity.GetComponent<HealthComponent>().health;
        }
        return 0;
    }
    /**
     * @brief Increases the score of an entity.
     *
     * Adds the specified amount to the entity's score if it has a ScoreComponent and is alive.
     *
     * @param entity The entity whose score will be increased.
     * @param amount The amount to add to the score.
     */
    void IncreaseScore(Entity entity, int amount) {
        if (!entity.IsAlive()) return;
        if (entity.HasComponent<ScoreComponent>()) {
            entity.GetComponent<ScoreComponent>().score += amount;
        }
    }
    /**
     * @brief Handles the death of an entity.
     *
     * Awards score to the player if the dead entity was killed by a player bullet, triggers an explosion
     * animation, and marks the entity for deletion (except for type 7 entities).
     *
     * @param deadEntity The entity that has died.
     * @param killerType The type of the entity that caused the death.
     */
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
    /**
     * @brief Creates an explosion animation for an enemy.
     *
     * Creates an explosion entity at the enemy's position with appropriate components for animation.
     * Optionally suppresses the sound effect for massive kills.
     *
     * @param enemy The enemy entity to animate the explosion for.
     * @param massiveKill Indicates if the explosion is part of a massive kill (e.g., nuke).
     */
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
    /**
     * @brief Handles an enemy attack on the player.
     *
     * Applies damage to the player based on the enemy type and marks the enemy for deletion if applicable.
     * Plays a sound effect for the enemy's death.
     *
     * @param player The player entity being attacked.
     * @param enemy2 The enemy entity attacking the player.
     */
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