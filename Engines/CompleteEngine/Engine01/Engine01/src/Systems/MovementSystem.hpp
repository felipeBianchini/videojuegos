#ifndef MOVEMENTSYSTEM_HPP
#define MOVEMENTSYSTEM_HPP

#include "../Components/RigidBodyComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../Components/SpriteComponent.hpp"
#include "../Components/EntityTypeComponent.hpp"
#include "../ECS/ECS.hpp"

/**
 * @class MovementSystem
 * @brief A system for handling entity movement and collision within an Entity-Component-System (ECS) architecture.
 *
 * This system manages entities with RigidBodyComponent, TransformComponent, SpriteComponent, and EntityTypeComponent.
 * It handles movement updates, boundary collisions, projectile behavior, and specific movement patterns for different
 * entity types, such as player, enemies, and projectiles.
 */
class MovementSystem : public System {
public:
    /**
     * @brief Constructor for the MovementSystem.
     *
     * Initializes the system and specifies that entities must have RigidBodyComponent, TransformComponent,
     * SpriteComponent, and EntityTypeComponent to be managed.
     */
    MovementSystem() {
        RequiredComponent<RigidBodyComponent>();
        RequiredComponent<TransformComponent>();
        RequiredComponent<SpriteComponent>();
        RequiredComponent<EntityTypeComponent>();
    }

private:
    /**
     * @brief Handles entity bouncing behavior at screen borders.
     *
     * Reverses the entity's velocity when it hits the screen borders, based on its position and sprite size.
     *
     * @param w The width of the game window.
     * @param h The height of the game window.
     * @param transform The TransformComponent of the entity, containing position and scale.
     * @param rigidBody The RigidBodyComponent of the entity, containing velocity.
     * @param sprite The SpriteComponent of the entity, containing width and height.
     * @param type The entity type, used to determine specific behavior (e.g., vertical bounce exclusion).
     */
    void BounceInBorders(double w, double h, TransformComponent& transform, RigidBodyComponent& rigidBody, SpriteComponent& sprite, int type) {
        double posX = transform.position.x + sprite.width * transform.scale.x;
        double posY = transform.position.y + sprite.height * transform.scale.y;
        if (posX >= w) {
            rigidBody.velocity.x *= -1;
        }
        else if (posX - (sprite.width / 2) <= 0) {
            rigidBody.velocity.x *= -1;
        }
        if (type != 3) {
            if (posY >= h) {
                rigidBody.velocity.y *= -1;
            }
            else if (posY - (sprite.height / 2) <= 0) {
                rigidBody.velocity.y *= -1;
            }
        }
    }
    /**
     * @brief Checks if projectiles are outside the screen and marks them for removal.
     *
     * If a projectile's position is beyond the screen boundaries, it is marked for deletion.
     *
     * @param x The x-coordinate of the projectile.
     * @param y The y-coordinate of the projectile.
     * @param w The width of the game window.
     * @param h The height of the game window.
     * @param entity The entity to check, potentially marked for removal.
     */
    void CheckProjectilesPosition(double x, double y, double w, double h, Entity entity) {
        if (x > w || y > h) {
            entity.Kill();
        }
    }
    /**
     * @brief Updates Enemy2 movement to follow the player.
     *
     * Adjusts the entity's velocity to move toward the player based on their relative positions.
     *
     * @param player The player entity to follow.
     * @param transform The TransformComponent of the enemy, containing its position.
     * @param rigidBody The RigidBodyComponent of the enemy, containing its velocity.
     */
    void Enemy2FollowUp(Entity player, TransformComponent& transform, RigidBodyComponent& rigidBody) {
        if (!player.HasComponent<TransformComponent>()) return;
        auto& playerPosition = player.GetComponent<TransformComponent>();
        glm::vec2 toPlayer = playerPosition.position - transform.position;
        float distance = glm::length(toPlayer);
        if (distance > 1.0f) {
            glm::vec2 direction = glm::normalize(toPlayer);
            float speed = 100.0f;
            rigidBody.velocity = direction * speed;
        }
        else {
            rigidBody.velocity = glm::vec2(0.0f);
        }
    }
    /**
     * @brief Updates Enemy3 movement with random direction changes.
     *
     * Randomly changes the entity's velocity direction while maintaining its speed.
     *
     * @param rigidBody The RigidBodyComponent of the enemy, containing its velocity.
     */
    void Enemy3Movement(RigidBodyComponent& rigidBody) {
        if (rand() % 100 < 1) {
            double speed = glm::length(rigidBody.velocity);
            int direction = (rand() % 2 == 0) ? 1 : -1;
            if (rigidBody.velocity.x != 0.0f) {
                rigidBody.velocity = glm::vec2(0.0f, speed * direction);
            }
            else {
                rigidBody.velocity = glm::vec2(speed * direction, 0.0f);
            }
        }
    }
    /**
     * @brief Ensures the player stays within screen boundaries.
     *
     * Clamps the player's position to prevent it from moving outside the screen.
     *
     * @param player The player entity to check.
     * @param screenWidth The width of the game window.
     * @param screenHeight The height of the game window.
     */
    void CheckPlayerPosition(Entity player, int screenWidth, int screenHeight) {
        auto& transform = player.GetComponent<TransformComponent>();
        auto& sprite = player.GetComponent<SpriteComponent>();
        double spriteWidth = sprite.width * transform.scale.x;
        double spriteHeight = sprite.height * transform.scale.y;
        if (transform.position.x < 0) {
            transform.position.x = 0;
        }
        else if (transform.position.x + spriteWidth > screenWidth) {
            transform.position.x = screenWidth - spriteWidth;
        }
        if (transform.position.y < 0) {
            transform.position.y = 0;
        }
        else if (transform.position.y + spriteHeight > screenHeight) {
            transform.position.y = screenHeight - spriteHeight;
        }
    }

public:
    /**
     * @brief Updates the positions and behaviors of managed entities.
     *
     * Iterates through entities, updates their positions based on velocity and delta time, and applies
     * specific movement behaviors (e.g., bouncing off borders, following the player, or random movement)
     * depending on the entity type.
     *
     * @param dt Delta time since the last update, used for time-based movement calculations.
     * @param windowHeight The height of the game window.
     * @param windowWidth The width of the game window.
     * @param player The player entity, used for specific interactions like enemy follow-up.
     */
    void Update(double dt, int windowHeight, int windowWidth, const Entity player) {
        for (auto entity : GetSystemEntiities()) {
            if (!entity.HasComponent<RigidBodyComponent>() ||
                !entity.HasComponent<TransformComponent>() ||
                !entity.HasComponent<EntityTypeComponent>()) {
                continue;
            }
            auto& rigidBody = entity.GetComponent<RigidBodyComponent>();
            auto& transform = entity.GetComponent<TransformComponent>();
            auto& sprite = entity.GetComponent<SpriteComponent>();
            int type = entity.GetComponent<EntityTypeComponent>().entityType;
            transform.position.x += rigidBody.velocity.x * dt;
            transform.position.y += rigidBody.velocity.y * dt;
            double width = static_cast<double>(windowWidth);
            double height = static_cast<double>(windowHeight);
            if (type == 3 || type == 6) {
                if (entity.HasComponent<IsEntityInsideTheScreenComponent>() &&
                    entity.GetComponent<IsEntityInsideTheScreenComponent>().isEntityInsideTheScreen) {
                    if (type == 3) {
                        BounceInBorders(width, height, transform, rigidBody, sprite, type);
                    }
                    else {
                        Enemy3Movement(rigidBody);
                        BounceInBorders(width, height, transform, rigidBody, sprite, type);
                    }
                }
            }
            else if (type == 2 || type == 4 || type == 13) {
                CheckProjectilesPosition(transform.position.x, transform.position.y, width, height, entity);
            }
            else if (type == 5) {
                Enemy2FollowUp(player, transform, rigidBody);
            }
            else if (type == 1) {
                CheckPlayerPosition(entity, windowWidth, windowHeight);
            }
        }
    }
};

#endif // MOVEMENTSYSTEM_HPP
