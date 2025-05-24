#ifndef MOVEMENTSYSTEM_HPP
#define MOVEMENTSYSTEM_HPP

#include "../Components/RigidBodyComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../Components/SpriteComponent.hpp"
#include "../Components/EntityTypeComponent.hpp"
#include "../ECS/ECS.hpp"

class MovementSystem : public System {
public:
    MovementSystem() {
        RequiredComponent<RigidBodyComponent>();
        RequiredComponent<TransformComponent>();
        RequiredComponent<SpriteComponent>();
        RequiredComponent<EntityTypeComponent>();
    }

private:
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

    void CheckProjectilesPosition(double x, double y, double w, double h, Entity entity) {
        if (x > w || y > h) {
            entity.Kill();
        }
    }

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

public:
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
            else if (type == 2 || type == 4) {
                CheckProjectilesPosition(transform.position.x, transform.position.y, width, height, entity);
            }
            else if (type == 5) {
                Enemy2FollowUp(player, transform, rigidBody);
            }
        }
    }
};

#endif // MOVEMENTSYSTEM_HPP
