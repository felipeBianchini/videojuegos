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

    void CheckEnemy1Movements(double w, double h, TransformComponent& transform, RigidBodyComponent& rigidBody) {
        bool isFullyInside = transform.position.x > 0 && transform.position.x < w;
        if (isFullyInside) {
            if (transform.position.x <= 0) {
                rigidBody.velocity.x *= -1;
            }
            else if (transform.position.x >= w) {
                transform.position.x = w;
                rigidBody.velocity.x *= -1;
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

    void Update(double dt, int windowHeight, int windowWidth, Entity player) {
        if (!player.HasComponent<TransformComponent>()) {
            return;
        }

        for (auto entity : GetSystemEntiities()) {
            if (!entity.HasComponent<RigidBodyComponent>() ||
                !entity.HasComponent<TransformComponent>() ||
                !entity.HasComponent<EntityTypeComponent>()) {
                continue;
            }

            auto& rigidBody = entity.GetComponent<RigidBodyComponent>();
            auto& transform = entity.GetComponent<TransformComponent>();
            int type = entity.GetComponent<EntityTypeComponent>().entityType;

            transform.position.x += rigidBody.velocity.x * dt;
            transform.position.y += rigidBody.velocity.y * dt;

            double width = static_cast<double>(windowWidth);
            double height = static_cast<double>(windowHeight);

            if (type == 3) {
                CheckEnemy1Movements(width, height, transform, rigidBody);
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
